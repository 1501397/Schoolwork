//Mitä ohjelma tekee:   Kun painetaa switchiä niin näyttö pimenee mutta laskuri laskee, 
//            kun nappia painetaan uudestaan näytöt syttyy ja timeri pysähtyy.

//Arduino C bittiohjausm��ritykset
int LD1 = 8;
int LD2 = 9;

char testi;

//GNU C bittim��ritykset
#define LED1 PORTB0
#define LED2 PORTB1
#define LED3 PORTB5
#define PZ PORTD6

#define SW1   0b00000100
#define SW2   0b00001000
#define SW3   0b00010000
#define SW4   0b00100000
#define KV_MAX 100      // Kv-laskurin maksimiarvo
#define ANY_SW (~PIND & SW1) | (~PIND & SW2) | (~PIND & SW3) | (~PIND & SW4)

#define S_SEC PORTD3    //1/100sek
#define K_SEC PORTD4    //1/10 sek ON/OFF
#define SEC   PORTD5    //1sek ON/OFF
#define COMP_ARVO 20000     //0,01s COMP arvo. COMP = vertailu
#define KELLOTAHTI 0b00001010
#define KELLOSTOP 0b00000000

unsigned char s_sec = 0;
unsigned char k_sec = 0;
unsigned char sec = 0;
unsigned char kv_ctr = 0;


ISR(INT0_vect)
{

  if (TCCR1B) {

                //Jos kello ON -> pysäytetään Timer1/kello
    TCCR1B = KELLOSTOP;
  }
  else {
    s_sec = 0;        //jos kello OFF -> Käynnistetään Timer1/kello CK = CK/8 & autonollaus
    k_sec = 0;
    sec = 0;
    TCNT1 = 0;
    TCCR1B = KELLOTAHTI;
  }

  EIMSK &= 0b11111110;
  kv_ctr = KV_MAX;

  //INT0 keskeytys OFF
  //Kytkinvärähtelylaskuri maksimiin.

}

ISR(TIMER1_COMPA_vect) {
  s_sec++;

  if (s_sec == 10) {

    s_sec = 0;
    k_sec++;

    if (k_sec == 10) {
      k_sec = 0;
      sec++;

      if (sec == 10) {
        sec = 0;
      }
    }
  }
}

void kv_pois(void) {          //Tällä poistetaan kytkinvärähtely mistä tahansa SW:sta.

  if (~PIND & SW1)
    kv_ctr = KV_MAX;
  else
    kv_ctr--;

  if (kv_ctr == 0) {
    EIMSK = 0x01;
  }

}


void mux_naytto(void) {

  PORTB &= 0b11110000;
  PORTB |= s_sec;     //1/100 sekunnit 4511-ohjaimelle
  PORTD |= 0b00111000;
  PORTD &= 0b11110111;


  delay(1);
  
  PORTB &= 0b11110000;
  PORTB |= k_sec;     //1/10 sekunnit 4511-ohjaimelle
  PORTD |= 0b00111000;
  PORTD &= 0b11011111;
              
  delay(1);

  PORTB &= 0b11110000;
  PORTB |= sec;     //sekunnit 4511-ohjaimelle
  PORTD |= 0b00111000;
  PORTD &= 0b11101111;

  delay(1);
}

// the setup function runs once when you press reset or power the board
void setup() {

  //Porttien aktivointi
  PORTB |= 0b00111111; //Ledit OFF
  DDRB |= 0b00111111; //PORTB:n 6 alinta linjaa OUTPUT

  PORTD |= 0b00111100; //Piezo pois p��lt�
  DDRD |= 0b00111000; //Piezo on OUTPUT

  EICRA &= 0b11111100;
  EIMSK |= 0x01;

  TCCR1A = 0b00000000;
  TCCR1B = KELLOSTOP;
  OCR1A = COMP_ARVO;
  TIMSK1 = 0x02;

  sei();          //Master interrupt on
              //SREG |= 0b10000000;
}



// the loop function runs over and over again until power down or reset
void loop() {

  if (kv_ctr) {
    kv_pois();      //Jos kytkinvärähtely on päällä -> käydään poistamassa värähtelyä
    
  }


  if (TCCR1B)
    PORTB = 0x0F;
  else
    mux_naytto();   //

}
