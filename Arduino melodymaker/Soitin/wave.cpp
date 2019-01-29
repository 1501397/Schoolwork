#include <ac_int.h>

// Voidaan määritellä erilaisilla bittimäärillä olevia kokonaislukuja 
// "ac_int<3,false> i" tarkoittaa 3 bitin etumerkitöntä kokonaislukua.

// Alla oleva funktio aktivoituu jokaisella kellopulssilla. Esimerkiksi DEO-NANO:ssa kello on 50 MHz.
// => Funktiota "kutsutaan" 50 miljoonaa kertaa sekunnissa.

#define CLOCKRATE 50000000
#define SINTAB_SIZE 32

static ac_int<12,false> SINTAB[SINTAB_SIZE] = {
    2048,2447,2831,3185,3495,3750,3939,4056,4095,4056,3939,3750,3495,3185,2831,2447,
    2048,1648,1264,910,600,345,156,39,0,39,156,345,600,910,1264,1648
    } ;

void wave (ac_int<16,false> &freq, ac_int<12,false> &da)	
{
// <freq> on taajuus, jonka tämä moduli tuottaa. Annetaan parametrina "kutsuttaessa".
// <da>   ohjaus, jolla sinisignaali muodostetaan D/A -muuntimella

    static int ix = 0 ;         // Tämä on se SINI-taulukon arvo, joka laitetaan D/A -muuntimelle
    static int n = 0 ;          // Laskemme tällä kellopulsseja => milloin aika laittaa seuraava D/A
    static int interval = 1 ;   // Näin monen kellopulssin välein vaihdetaan arvoa
    
    static ac_int<12,false> da_out = 0 ;       // Tätä arvoa lähetetään D/A -muuntimelle

    if ( freq == 0 )                            // Jos pyydetään 0-taajuutta
    {
        da_out = 0 ;                            // Hiljennetään taajuusgeneraattori
    }
    else if ( ++n >= interval )
    {
        da_out = SINTAB[ix] ;                   // Otetaan sinin arvo taulukosta
        ++ix ;                                  // Mennään seuraavaan arvoon
        
        if ( ix >= SINTAB_SIZE )                // Tultiinko taulukon loppuun?
        {
            ix = 0 ;                            // Sitten pitää aloittaa alusta
        }
        
        interval = CLOCKRATE/(int)freq/32 ;     // Näin monen pulssin jälkeen siirrytään seur. arvoon
        n = 0 ;                                 // Lasketaan seuraavaan intervalliin
    }    
    
    da = da_out ;
}
