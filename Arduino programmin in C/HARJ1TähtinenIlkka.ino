// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       HARJ1.ino
    Created:	12.9.2018 13.36.36
    Author:     LAPTOP-DOJ5EPN9\Tomi Rämö
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
#define PORTB
#define DDRB

// The setup() function runs once each time the micro-controller starts
void setup()
{
	//Porttien aktivointi
	PORTB |= 0b00111111; //Ledit off
	DDRB |= 0b00111111; //PortB:n 6 alinta linjaa output

}

// Add the main program code into the continuous loop() function
void loop()
{
	PORTB &= 0b11001100; //neljä lediä on
	delay(1000);
	PORTB |= 0b00110011;
}
