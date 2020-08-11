using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Kilpailu‐luokka on geneerinen sisältäen kaksi tyyppiparametria, joita käytetään Suoritus‐luokan
//tyypittämiseen(eli ovat vastaavat kuin Suoritus‐luokassa). Luokka sisältää seuraavat elementit: 
// automaattiset ominaisuudet Nimi ja Suoritukset, joista jälkimmäinen tyypitetään luokan
//tyyppiparametrein määritellyn Suoritus‐tyyppisten olioiden listaksi.
// konstruktori, jossa ominaisuuden Suoritukset arvoksi sijoitetaan uusi tyyppiparametrein määritetty
//Suoritus‐olioiden lista.

namespace KilpailuIT
{
    class Kilpailu
    {
        public string Nimi {get; set;}
        public double Suoritukset { get; set; }
    }
}
