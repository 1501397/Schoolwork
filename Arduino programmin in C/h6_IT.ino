// Ledien kirkkaus säätö
//SW1 asettaa pulssisuhteeksi 0 %   
//SW2 pienentää pulssisuhdetta (max -> min siirtymä n. 5s aikana)   
//SW3 kasvattaa pulssisuhdetta (min -> max siirtymä n. 5s aikana)   
//SW4 asettaa pulssisuhteeksi 100 % 

// gnu C bittim��ritykset
#define LED1 PORTB0
#define LED2 PORTB1
#define LED3 PORTB2
#define LED4 PORTB3
#define LED5 PORTB4
#define LED6 PORTB5

#define PZ   PORTD6

#define SW1 0b00000100
#define SW2 0b00001000
#define SW3 0b00010000
#define SW4 0b00100000

#define JAKSO 20
#define ON1 5
#define ON2 10
#define ON3 15
#define ON4 20


unsigned char on_aika = 0;
int x = 0;
int y = 0;
// ledin ohjaus 1 jakson ajan
void led_pwr(unsigned on_aika)      
{
    PORTB &= 0b11000000;    // led ON 
    delay(on_aika);       // ON jakson viive
    PORTB |= 0b00111111;    // led OFF 
    delay(JAKSO - on_aika);     // T - ON jakson viive
}
void setup() {

  // porttien aktivointi
  PORTB |= 0b00111111;    // Ledit pakotetaan poist p��lt�
  DDRB |= 0b00111111;     // PORTB:n 6 alinta linjaa Output
  PORTD |= 0b01111100;    // pietso OFF p��lt� ja yl�svedot ON (0 1 pietso) (1 1 1 1 4 kytkint�) 0 0
  DDRD |= 0b01000000;     // PORTD:n 7 linja output ja SW:T input
}

// the loop function runs over and over again until power down or reset
void loop() {

  for (x=0 ;x < 20; x++)
    {
        led_pwr (on_aika);
    }
  //if (on_aika == 20)
  //  on_aika = 0;
  //else
  //on_aika++;
  

  
  

  if (~PIND & SW1)          //if swtich ON
  {
    on_aika = 0;
  }

  if (~PIND & SW2)
  {
    if (on_aika == 0)
      on_aika = 0;
    else
      on_aika--;

    for (x = 0; x < 10; x++)
    {
      led_pwr(on_aika);

      if (PIND & SW2)
        break;
    }
  }
  
  if (~PIND & SW3)
  {
    if (on_aika == 20)
      on_aika = 20;
    else
      on_aika++;

    for (x = 0; x < 10; x++)
    {
      led_pwr(on_aika);

      if (PIND & SW3)
        break;
    }
  }
  
  if (~PIND & SW4)
  {
    on_aika = 20;

    for (x = 0; x < 10; x++)
      {
        led_pwr(on_aika);

        if (PIND & SW4)
          break;
      }
  }
}


}
