#include <ac_int.h>

// #define CLOCKRATE 50000000
#define OCTAVE_SIZE 14

// Moduli, joka ohjaa tätä modulia, syöttää melodian kirjaimilla
// UKKO NOOA: 'c', 's', 'c', 's', 'c', 's', 'e', ...

//  's' 'c' C#'C' 'd' D#'D' 'e' 'f'  F#'F' 'g' G#'G''a'  A#'A''b'  '2'
static ac_int<12,false> OCTAVE_TONES[OCTAVE_SIZE] = {
    0,  262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 493, 512
    } ;

void tonegenerator (ac_int<16, false> &tone, ac_int<16,false> &freq)
{
// <tone> on nuotti, joka halutaan ulos. Tämä tulee parametrina
// <freq> on taajuus, joka komennetaan D/A muunnin moduli <wave> tuottamaan

    ac_int<16, false> freq_out = 0 ;            // D/A muuntimelle lähetettävä ohjaus

	switch (tone)
	{
	case 's': freq_out = OCTAVE_TONES[0];
		break;
	case 'c': freq_out = OCTAVE_TONES[1];
		break;
	case 'C': freq_out = OCTAVE_TONES[2];
		break;
	case 'd': freq_out = OCTAVE_TONES[3];
		break;
	case 'D': freq_out = OCTAVE_TONES[4];
		break;
	case 'e': freq_out = OCTAVE_TONES[5];
		break;
	case 'f': freq_out = OCTAVE_TONES[6];
		break;
	case 'F': freq_out = OCTAVE_TONES[7];
		break;
	case 'g': freq_out = OCTAVE_TONES[8];
		break;
	case 'G': freq_out = OCTAVE_TONES[9];
		break;
	case 'a': freq_out = OCTAVE_TONES[10];
		break;
	case 'A': freq_out = OCTAVE_TONES[11];
		break;
	case 'b': freq_out = OCTAVE_TONES[12];
		break;
	case '2': freq_out = OCTAVE_TONES[13];
		break;
	default: freq_out = 0;
		break;
	}
    
	freq = freq_out ;
}
