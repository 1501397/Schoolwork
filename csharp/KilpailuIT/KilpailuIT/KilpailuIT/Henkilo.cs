using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

//Henkilo‐luokka toteuttaa rajapinnan IOsallistuja sisältäen seuraavat elementit: 
// automaattiset ominaisuudet Id, Etunimi ja Sukunimi 
// ominaisuus Nimi, jonka get‐metodi palauttaa ominaisuuksien Sukunimi ja Etunimi arvot
//välilyönnillä eroteltuna ja jonka set‐metodissa sijoitetaan ominaisuuteen sijoitettavasta arvosta
//saatavat merkkijonot ominaisuuksiin Sukunimi ja Etunimi.Jos sijoitettava arvo ei ole muodoltaan
//oikea(eli ei sisällä kahta välilyönnillä eroteltua merkkijonoa), heitetään poikkeus virhetekstillä 
//”Henkilön nimi on oltava muodossa sukunimi etunimi.”. 

namespace KilpailuIT
{
    class Henkilo : IOsallistuja
    {
        

        public Henkilo(string nimi)
        {
            nimi = Nimi;
            //Sukunimi = suku;
            //Etunimi = etu;
        }

        public string Etunimi { get; set; }
        public string Sukunimi { get; set; }
        public int Id { get; set; }



        public string Nimi
        {
            get
            {
                
                return $"{Sukunimi} {Etunimi}";
            }

            set
            {
                string[] sanat = value.Split();
                if (sanat.Length == 2)
                {
                    Sukunimi = sanat[0];
                    Etunimi = sanat[1];
                }
                else
                {
                    throw new Exception("Henkilön nimi on oltava muodossa sukunimi etunimi...");
                }
            }
        }

        public override string ToString()
        {
            return Nimi;
        }


    }
}
