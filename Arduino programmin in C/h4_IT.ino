

//Toiminta:
//SW1 = käynnistää ohjelman
// ohjelma on reaktiotesteri joka askeltaa ledejä
// reagoint tapahtuu painamalla SW4
// SÄÄNNÖT: ennakointi = häviät, myöhästy: häviät




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


#define SW_NAKSU 2        // kytkimen painallus��nen pituus

//globaalit muuttujat

char numero = 1;
char stop = 0;        //pys�ytys muuttuja
char alarm = 0;       //h�lylippu
int x;            //for loop 1. apumuuttuja
int y;            //for loop 2. apumuuttuja
int z;            //for loop 3. apumuuttuja
unsigned int viive;

void win(void)
{
  piezo_beep(50);
  delay(50);
  piezo_beep(50);

}
void haly(void)             // vilkuttaa ledej�
{
  piezo_beep(100);
  PORTB = 0b11101010;
  delay(100);
  PORTB = 0b11010101;
  delay(100);
  PORTB = 0b11101010;
  delay(100);
  PORTB = 0b11010101;

}
void piezo_beep(char aika)        // PZ yksi jakso
{
  PORTD &= ~(1 << PZ);        // PZ ON puolijakso
  delay(aika);
  PORTD |= (1 << PZ);         // PZ OFF puolijakso
  delay(aika);
}
//ledin askellus 1 pyk�l��
void led_run(void)
{
  PORTB = ~numero;          // kuula Ledeille
  piezo_beep(1);            // lyhyt ��ni
  numero <<= 1;           // askelletaan kuulaa yhdell� pyk�l�ll�
  if (numero == 64)
    numero = 1;
}
void setup() {

  // porttien aktivointi
  PORTB |= 0b00111111;        // Ledit pakotetaan pois p��lt�
  DDRB |= 0b00111111;         // PORTB:n 6 alinta linjaa Output
  PORTD |= 0b01111100;        // pietso pois p��lt� ja yl�svedot on 0 1 pietso 1 1 1 1 4 kytkint� 0 0
  DDRD |= 0b01000000;         // PORTD:n 7 linja output ja SW:T input
}

// the loop function runs over and over again until power down or reset
void loop() 
{
  
  while (PIND & SW1);   //STOP tila -> jumitus niin kauan kun sw4 ei painettu   
  numero = 1;
  stop = 0;
  alarm = 0;
  PORTB = ~numero;          // nollataan ledit
  piezo_beep(SW_NAKSU);       // lyhyt ��ni
  viive = 1000 + rand() % 2000;   // aloittaa randomisti 1-3 sekuntin v�lilt�
                    // ALKUVIIVE-tila
  for (z = 0; z < viive; z++)
  {
    if (~PIND & SW4) 
    {
      alarm = 1;
      haly();
      break;
    }
    delay(1);
  }

  // Joko RUN tai H�LY tila
  if (!alarm)                 // Jos ei olla alarm tilassa
  {
    for (x = 0; x < 6; x++)
    {
      for (y = 0; y < 50; y++)
      {
        if (~PIND & SW4)        // Jos SW4 painettu ajoissa
        {
          stop = 1;
          piezo_beep(SW_NAKSU);
          win();
          break;
        }
        delay(1);
      }
      if (stop)
        break;
      else
      {
        numero <<= 1;         // askelletaan reaktiotesteri� yhdell� pyk�l�ll�
        PORTB = ~numero;        // reaktiotesteri start
        piezo_beep(SW_NAKSU);     // lyhyt ��ni
      }
    }
    if (!stop)                // jos ei paina nappia
      haly();               // p��st�� �rsytt�v�n ��nen
  }
}
