// Säätää ledian kirkkautta
//Toiminta kuten edellisessä harjoituksessa, mutta säätö on 1024 pykäläinen



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



 int on_aika = 0;


void setup() {

  // porttien aktivointi
  PORTB |=  0b00111111;     // Ledit pakotetaan poist p��lt�
  DDRB |=   0b00111111;     // PORTB:n 6 alinta linjaa Output
  PORTD |=  0b01111100;     // pietso OFF p��lt� ja yl�svedot ON (0 1 pietso) (1 1 1 1 4 kytkint�) 0 0
  DDRD |=   0b01000000;     // PORTD:n 7 linja output ja SW:T input

  // timer 1 asetukset
  //TCCR1A |= (1 << COM1A1);            // PB1 -Led2 non-inverted pwm
  TCCR1A |= (1 << COM1B1) | (1 << COM1B0);    // PB2- Led3 inverted pwm
  TCCR1A |= (1 << WGM10);             // 8 bit 
  TCCR1A |= (1 << WGM11);             // 10 bit + 8 bit
  TCCR1A |= (1 << WGM12);             // Fast PWM 

  TCCR1B |= (1 << CS10);              // timer 1 ON, F = 16MHz

}



// the loop function runs over and over again until power down or reset
void loop() 
{

  //OCR1A = 1023;
  OCR1B = on_aika;


  if (~PIND & SW1)          //if swtich ON
  {
    on_aika = 0;          // led OFF
  }

  if (~PIND & SW2)          
  {
    if (on_aika < 1023)       // kirkastaa
      on_aika++;
    else
      on_aika = 1023;
  }

  if (~PIND & SW3)
  {
    if (on_aika > 0)        // himment��
      on_aika--;
    else
      on_aika = 0;
    
  }

  if (~PIND & SW4)
  {
    on_aika = 1023;         // led ON
  }
  
  delay(1);
}
