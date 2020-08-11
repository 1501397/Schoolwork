using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//IOsallistuja‐rajapinta sisältää pakotteen merkkijonotyyppisestä ominaisuudesta Nimi, jolla on vähintään
//get‐metodi ja kokonaislukutyyppisestä ominaisuudesta Id, jolla on vähintään get‐metodi.

namespace KilpailuIT
{
    interface IOsallistuja
    {
        string Nimi { get; }
        int Id { get; }


    }
}
