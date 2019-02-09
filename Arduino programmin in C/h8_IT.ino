// Ohjelma askeltaa binäärisesti ylös- ja alaspäin, kytkin 1 askeltaa ylös ja kytkin 2 askeltaa alas.

//SW-määrittely

#define SW1   0b00000100
#define SW2   0b00001000
#define SW3   0b00010000
#define SW4   0b00100000
#define ANY_SW (~PIND & SW1) | (~PIND & SW2) | (~PIND & SW3) | (~PIND & SW4) 

#define KV_MAX 100            //kytkinvärähtelylle maksimi-arvo
#define KV_POIS 3           //värähtelyn poistolle arvo


char ohjaus = 0, kv_laskuri, kv_on;    //Ohjaus nollaan

void kv_pois();             //Funktio, kytkinvärähtelyn poiston 



ISR(INT0_vect)            //Int0 keskeytys
{
  ohjaus++;           

  if (ohjaus == 64)
  {
    ohjaus = 0;         
  }

  PORTB = ~ohjaus;        

  EIMSK &= 0b11111110;      //Int0 off-tilaan
  kv_laskuri = KV_MAX;      //Arvoksi maksimiarvo
  kv_on = KV_POIS;
}
ISR(INT1_vect)            //Int1-keskeytys
{
  if (ohjaus == 0)
  {
    ohjaus = 63;        
  }

  ohjaus--;           

  PORTB = ~ohjaus;        
  EIMSK &= 0b11111101;      //Int1 off-tilaan
  kv_laskuri = KV_MAX;      //laskuri max
  kv_on = 1;            
}

void kv_pois(void)          //Kytkinvärähtelyn poisto
{
  if (kv_laskuri)         

    if (ANY_SW)         

      kv_laskuri = KV_MAX;  

    else

      kv_laskuri--;     

  if (kv_laskuri == 0)      
  {
    kv_on--;          
    delay(5);         
    if (kv_on == 0)       
    {
      EIFR |= 0b00000001;         //INT0 nollataan
      EIMSK |= 0b00000011;        //sammutetaan keskeytykset
    }
  }


}
void setup() {  //porttimaarittelyt

  PORTB |= 0b00111111;        //Led off
  DDRB |= 0b00111111;         //Port B 0-5 output

  PORTD |= 0b01111100;        //piezo off
  DDRD |= 0b01000000;         // piezon OUTPUT

  EICRA &= 0b11110000;
  EICRA |= 0b00000010;
  EIMSK |= 0b00000011;        //INT0 ja INT1 ON
  sei();                //Master keskeytys on
                
}



void loop()
{

  if (kv_on)            //Odotetaan INT0 keskeytystä
  {
    kv_pois();

  }

}
