#include <ac_int.h>

#define CLOCKRATE       50000000            // 1 second
#define WN              (CLOCKRATE/4)       // 1/4 s
#define HN              (WN/2)              // 1/8 s
#define QN              (HN/2)              // 1/16 s

typedef struct 
{
    ac_int<16, false> tone ;            // Haluttu nuotti
    int               length ;          // Nuotin kesto kellojaksoina
}
 TONE_TYPE ;
    
TONE_TYPE melody[] = {
    {'e',QN}, {'s',QN/2},
    {'e',QN}, {'s',QN},
    {'e',QN}, {'s',QN/2},
    {'a',QN}, {'s',QN},

    {'g',QN}, {'s',QN/2},
    {'g',QN}, {'s',QN},
    {'g',QN}, {'s',QN/2},
    {'b',QN}, {'s',QN},

    {'a',QN}, {'s',QN/2},
    {'f',QN}, {'s',QN},
    {'g',QN}, {'s',QN/2},
    {'e',QN}, {'s',QN},

    {'f',HN}, {'s',HN},
    
    {'s',10*WN},
    
    {'R', 0}                    // 'R' -> Restart        
 } ;
 
void melodymaker (ac_int<16, false> &tone)
{
// <tone> on nuotti, ohjaus seuraavalle modulille.

	static int tonepos = 0;				// Aloitamme nuotista 0
	static int N = 0;					// Kellopulssien laskuri
    ac_int<16, false> tone_out ;		// Tone out

	if (++N >= melody[tonepos].length)	// Nuotti soitettu loppuun?
	{
		N = 0;							// Aloitetaan ajastaminen alusta
		++tonepos;						// Mennään seuraavaan nuottiin

		if (melody[tonepos].tone == 'R')	// Aloitetaanko pimputus alusta
			tonepos = 0;				// Aloitetaan sitten alusta
	}
    
	tone_out = melody[tonepos].tone;	// Pyydetään taajuutta

	tone = tone_out ;
}
