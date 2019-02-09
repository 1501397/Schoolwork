
//tämä on koodilukko joka aukeaa 1,2,3,4 koodin ollessa oikein lukko avataan
// syötettäessä virheellinen koodi ohjlma hälyyttää.


// gnu C bittim��ritykset

// ledit

#define LED1 PORTB0
#define LED2 PORTB1
#define LED3 PORTB2
#define LED4 PORTB3
#define LED5 PORTB4
#define LED6 PORTB5

#define NOPEUS 100




// pietso

#define PZ   PORTD6

// kytkimet

#define SW1 0b00000100 
#define SW2 0b00001000
#define SW3 0b00010000
#define SW4 0b00100000

#define ANY_SW (~PIND & SW1 | ~PIND & SW2 | ~PIND & SW3 | ~PIND & SW4)
                // tosi jos joku kytkin on painettu

#define SW_NAKSU 2        // kytkimen painallus��nen pituus

//lukon tilat
#define START 0
#define FIRST 1 
#define SECOND  2
#define THIRD 3
#define OPEN  4
#define ALARM 5

#define KV_MAX 100      // kv-laskurin max arvo 100


//globaalit muuttujat

char nappi;         // kytkimen no.
char tila = 0;        // tilakoneen tilan no.
char alarm_flag = 0;        // h�ly lippu 0 = OFF, 1 = ON
char koodi[4] = {1,2,3,4};


// kytkimen lukeminen
void read_sw(void)      // palauttaa painetun SW:n numeron, jos mit��n ei painettu
{ 
  nappi = 0;        // palauttaa 0:n nappi muuttujaan
  if (~PIND & SW1)
    nappi = 1;

  if (~PIND & SW2)
    nappi = 2;

  if (~PIND & SW3)
    nappi = 3;
  
  if (~PIND & SW4)
    nappi = 4;
}
// kytkin v�r�htelyn poisto
void kv_pois(void)      // t��ll� poistetaan kytkinv�r�htely mist� tahansa kytkimest�
{
  unsigned char kv_ctr = KV_MAX;    // laskuri tappiin
  piezo_beep(SW_NAKSU);
  
  while (kv_ctr)
  {
    if (ANY_SW)
      kv_ctr = KV_MAX;
    else kv_ctr--;
  }


}
void haly(void)             // h�ly toiminto
{
  PORTB &= 0b00111100;
  piezo_beep(100);
  alarm_flag = 0;
}
void piezo_beep(char aika)        // PZ yksi jakso
{
  PORTD &= ~(1 << PZ);        // PZ ON puolijakso
  delay(aika);
  PORTD |= (1 << PZ);         // PZ OFF puolijakso
  delay(aika);
}


void setup() {

  // porttien aktivointi
  PORTB |= 0b00111111;        // Ledit pakotetaan pois p��lt�
  DDRB |= 0b00111111;         // PORTB:n 6 alinta linjaa Output
  PORTD |= 0b01111100;        // pietso pois p��lt� ja yl�svedot on 0 1 pietso 1 1 1 1 4 kytkint� 0 0
  DDRD |= 0b01000000;         // PORTD:n 7 linja output ja SW:T input

  tila = START;
}



// the loop function runs over and over again until power down or reset
void loop()
{
  
  read_sw();

  if (nappi)
  {
    kv_pois();              // poistetaan kytkinv�r�htelyt
    

    switch (tila)
    {
      case START:           // start toiminnot
        tila = FIRST;
        PORTB |= 0b00111111;    // ledit pois
        if (nappi != koodi[0])    // jos v��r� nappi, alustetaan nostetaan h�ly lippu
          alarm_flag = 1;
      break;
      
      case FIRST:           // first toiminnot
        tila = SECOND;
        if (nappi != koodi[1])
          alarm_flag = 1;
      break;

      case SECOND:          // second toiminnot
        tila = THIRD;
        if (nappi != koodi[2])
          alarm_flag = 1;
      break;

      case THIRD:           // third toiminnot
        if (nappi != koodi[3])
          alarm_flag = 1;

        if (alarm_flag == 1)    // jos h�lyliipu on ylh��ll� -> j�ly
          tila = ALARM;
        else            // muuten "avataan lukko"
          tila = OPEN;

      break;

      case ALARM:           // alarm toiminnot    
        haly();
        tila = START;

      break;

      case OPEN:            // open toiminnot
        PORTB &= 0b00110011;
        tila = START;

      break;
    }
  }
}
