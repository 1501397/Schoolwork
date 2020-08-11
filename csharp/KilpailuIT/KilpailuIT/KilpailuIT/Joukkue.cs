using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Joukkue‐luokka toteuttaa rajapinnan IOsallistuja sisältäen seuraavat elementit: 
// automaattiset ominaisuudet Id ja Nimi

namespace KilpailuIT
{
    class Joukkue : IOsallistuja
    {
        public string Nimi { get; set; }
        public int Id { get; set; }
    }
}
