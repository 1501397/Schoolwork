//Ohjelma askeltaa binäärisesti ylöspäin timeria käyttäen.

//SW-määrittely

#define SW1   0b00000100
#define SW2   0b00001000
#define SW3   0b00010000
#define SW4   0b00100000
#define ANY_SW (~PIND & SW1) | (~PIND & SW2) | (~PIND & SW3) | (~PIND & SW4)
#define COMPA2s  31250
//#define KV_MAX 100
//#define ALKUARVO_1s 49911



char ohjaus = 0;  //Ohjaus asetetaan aluksi nollaan





ISR(TIMER1_COMPA_vect)        //Timer 1 compa-keskeytysfunktio
{
  ohjaus++;           

  if (ohjaus == 0x40)       
  {
    ohjaus = 0;         
  }

  PORTB = ~ohjaus;        

}



void setup() {  //porttimaarittelyt

  PORTB |= 0b00111111;        
  DDRB |= 0b00111111;         

  PORTD |= 0b01111100;        
  DDRD |= 0b01000000;        

//Timer1 COMPA-asetukset
  TCCR1A &= 0x00;           
  TCCR1B &= 0b11111101;       
  TCCR1B |= 0b00001101;       
  OCR1A = COMPA2s;          //2s alkuarvo keskeytyksille
  TIMSK1 |= 0b00000010;       
  sei();                
              
}



void loop()
{



}
