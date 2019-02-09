//Ohjelma toteuttaa tennispelin, jossa kaksi pelaajaa voivat otella kolmeen pisteeseen asti. Tämän jälkeen ohjelma resetoidaan ja voidaan aloittaa alusta.

//lEDien ja piezojen määrittely

#define LED1 PORTB0
#define LED2 PORTB1      
#define LED3 PORTB2
#define LED4 PORTB3
#define LED5 PORTB4
#define LED6 PORTB5
#define PZ   PORTD6

#define ALKU 60000 //määritellään alkutasoksi 60000
#define TIME 1500   //ja ajaksi 1500    

//SW-määrittely

#define SW1   0b00000100
#define SW2   0b00001000
#define SW3   0b00010000
#define SW4   0b00100000
#define ANY_SW (~PIND & SW1) | (~PIND & SW2) | (~PIND & SW3) | (~PIND & SW4)


//Pelitilat, määritys
#define START  0
#define LEFT  1
#define RIGHT 2
#define POINTS  3
#define GAMEOVER  4

char ball, c_counter = 0, sw4_ok, sw1_ok;    
char  alarm = 0, p_t = 0, sw1_points = 0, sw4_points = 0, tila;



//Ohjelman funktioiden esittelyt
void oikealle();
void vasemmalle();
void start();
void points();
void p_turn();


void oikealle()
{
  ball = 1;             //Asetetaan ohjauksen arvoksi 1 
  p_t = 4;              //Asetetaan syöttövuoroksi 4
  tila = RIGHT;           //Asetetaan seuraavaksi tilaksi RIGHT
}
void vasemmalle()
{     
  ball = 64;            //Asetetaan ohjauksen arvoksi 64
  p_t = 1;              //Asetetaan syöttövuoroksi 1
  tila = LEFT;            // Asetetaan seuraavaksi tilaksi LEFT
}

void start()
{
                    //Start-funktiossa nollataan 
    PORTB = ~(0x40);        //Ledit
    alarm = 0;            //halytys
    c_counter = 0;       //keskeytyslaskuri
    sw1_points = 0;         //Molempien pisteet
    sw4_points = 0;
    p_t = 0;            //ja syöttövuoro
    tila = START;         //tilaksi palautetaan START

}
void points()
{
    OCR1A = ALKU;         //Palautetaan keskeytysten pulssien lukumäärä

    if (sw1_points == 3)        //jos sw1 pisteet on 3, sytytetään kolme alinta LEDiä
    {
      PORTB &= ~(1 << LED1);
      PORTB &= ~(1 << LED2);
      PORTB &= ~(1 << LED3);

    }
    if (sw1_points == 2)        //Jos sw1 pisteet on 2, sytytetään kaksi alinta LEDiä
    {
      PORTB &= ~(1 << LED1);
      PORTB &= ~(1 << LED2);
    }
    if (sw1_points == 1)        //jos sw1 pisteet on 1, sytytetään alin LED
    {
      PORTB &= ~(1 << LED1);
    }
    if (sw4_points == 3)        //Jos sw4 pisteet on 3, sytytetään kolme ylintä LEDiä
    {
      PORTB &= ~(1 << LED4);
      PORTB &= ~(1 << LED5);
      PORTB &= ~(1 << LED6);
    }
    if (sw4_points == 2)        //Jos sw4 pisteet on 2, sytytetään kaksi ylintä LEDiä
    {
      PORTB &= ~(1 << LED5);
      PORTB &= ~(1 << LED6);
    }
    if (sw4_points == 1)        // jos sw4 pisteet on 1, sytytetään ylin LED
    {
      PORTB &= ~(1 << LED6);
    }
    delay(TIME);            // pidetään 1500 ms viive, jonka ajan pisteet näkyvillä

    if ((sw1_points < 3) && (sw4_points < 3))
    {
      alarm = 0;            //Jos kummallakaan ei ole 3 pistettä, asetetaan alarm takaisin nollaan,
      PORTB = ~(0x40);        //sammutetaan kaikki LEDit
      p_turn();            // ja kutsutaan p_turn-funktiota
    }
    else
                      //muussa tapauksessa, eli toisella on 3 pistettä, asetetaan tilaksi GAMEOVER
        tila = GAMEOVER;




}
//Syöttövuoro
void p_turn()          
{
  if (p_t == 1)      
  {
     
    while(PIND & SW1){
      PORTB &= ~(1 << LED1);
    };
    p_t = 4;        
    ball = 1;       
    tila = RIGHT;     
  }
  else if (p_t == 4)      
  {
    
    while(PIND & SW4){
      PORTB &= ~(1 << LED6);
    };
    p_t = 1;        
    ball = 64;      
    tila = LEFT;      
  }
}

//Timer
ISR(TIMER1_COMPA_vect)        
{
  if (tila == RIGHT)      
  {
    PORTB = ~ball;      
    ball <<= 1;
    if (ball < 64)      
    {
      if (~PIND & SW4)    
      {
        alarm = 1;
      }
    }
    if (ball == 64)      
    {
      if (~PIND & SW4)    
      {
        tila = LEFT;    
        c_counter++;
      }
    }
    if (ball == 0)      
    {
      alarm = 1;        
    }

    if (alarm)          
    {
      PORTB = ~(0x40);    
      sw1_points++;      
      c_counter = 0;   
      tila = POINTS;      
    }
  }

  else if (tila == LEFT)    
  {
    ball >>= 1;       
    PORTB = ~ball;

    if (ball > 1)       
    {
      if (~PIND & SW1)    
      {
        alarm = 1;
      }
    }
    if (ball == 1)      
    {
      if (~PIND & SW1)    
      {
        tila = RIGHT;   
        c_counter++;
      }
    }
    if (ball == 0)      
    {
      alarm = 1;        
    }

    if (alarm)          
    { 
      PORTB = ~(0x40);   
      sw4_points++;      
      c_counter = 0;   
      tila = POINTS;      
    }

  }
  if (c_counter == 2)      
  {
    OCR1A = 50000;        
  }
  if (c_counter == 4)     
  {
    OCR1A = 40000;       
  }
  if (c_counter == 8)     
  {
    OCR1A = 30000;       
  }
  if (c_counter == 12)     
  {
    OCR1A = 20000;       
  }               
}


//Portit, määrittely
void setup() {  

  PORTB |= 0b00111111;        //Ledit off
  DDRB |= 0b00111111;         //Port B 0-5 output

  PORTD |= 0b01111100;        
  DDRD |= 0b01000000;        
                    
  TCCR1A &= 0x00;           
  TCCR1B &= 0b11111101;      
  TCCR1B |= 0b00001011;       
  OCR1A = ALKU;         
  TIMSK1 |= 0b00000010;       
  sei();                
  tila = START;           
}

void loop()
{
  switch (tila)
  {
  case START:             
    if (~PIND & SW1)      
      oikealle();       

    if (~PIND & SW4)      
      vasemmalle();

    break;
  case POINTS:          
    points();
    break;

  case GAMEOVER:          
    start();
    break;

  default:
    break;
  }
}
