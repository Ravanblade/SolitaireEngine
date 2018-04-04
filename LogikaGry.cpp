#include "LogikaGry.h"

LogikaGry::LogikaGry()
{
     utworzTalieKart();
     rozdajKarty();
     wynik = 0;
}

LogikaGry::~LogikaGry()
{

}

void LogikaGry::utworzTalieKart()
{
    for(int i = TAL_1; i < TAL_LAST; i++)
        T[i] = new Talia();

    T[TAL_G]->utworzTalie();
    T[TAL_G]->tasujTalie();
}

void LogikaGry::rozdajKarty()
{
    for(int i = TAL_1; i < TAL_S; i++)
        for(int j = 0; j < 5; j++)
            T[i]->dodajNaPoczatek(T[TAL_G]->wysunKarte());

    T[TAL_S]->dodajNaPoczatek(T[TAL_G]->wysunKarte());

/*    for(int i = TAL_1; i < TAL_S; i++)
    {
        cout << "Talia " << i << ":\n";
        T[i]->wyswietlTalie();
        cout << endl;
    }
*/
}

Talia *LogikaGry::zwrocTalie(RTalie rt)
{
   return T[rt];
}

bool LogikaGry::sprawdzOpcje()
{
    for(int i = TAL_1; i < TAL_G; i++)
    {
        if(T[i]->index(1) == NULL)
            continue;

        if(szacuj(T[TAL_S]->index(1)->nazwa, T[i]->index(1)->nazwa))
            return true;

    }
    if(T[TAL_G]->iloscKart() > 0)
        return true;
    else
    {
        for(int i = TAL_1; i < TAL_G; i++)
        {
            if(T[TAL_G]->index(1) == NULL)
                break;

            if(T[i]->index(1) == NULL)
                break;

            if(szacuj(T[TAL_G]->index(1)->nazwa, T[i]->index(1)->nazwa))
                return true;

        }
    }

    return false;
}

bool LogikaGry::polozKarteNaStos(RTalie a)
{
    if(T[a]->index(1) == NULL)
        return false;

    if(szacuj(T[TAL_S]->index(1)->nazwa, T[a]->index(1)->nazwa))
    {
        T[TAL_S]->dodajNaPoczatek(T[a]->wysunKarte());
        dodajPunkty(50);
    }
    else
        return false;

    return true;
}

bool LogikaGry::nowaKarta()
{
    if(T[TAL_G]->index(1) != NULL)
        T[TAL_S]->dodajNaPoczatek(T[TAL_G]->wysunKarte());
    else
        return false;

    return true;
}

bool LogikaGry::szacuj(string st, string k)
{
    short int wartoscS = -1;
    short int wartoscK = -1;

    if(st.empty() || k.empty())
        return false;

    for(int i = 0; i < 13; i++)
    {
        if(st == T[0]->nazwy(i))
            wartoscS = i;
        else if(k == T[0]->nazwy(i))
            wartoscK = i;
    }

    return ((wartoscS != -1) && (wartoscK != -1) &&((wartoscS-1 == wartoscK) || (wartoscS+1 == wartoscK)));
}


short int LogikaGry::pokazWynik()
{
   return wynik;
}

void LogikaGry::dodajPunkty(short int p)
{
    wynik += p;
}
void LogikaGry::odejmijPunkty(short int p)
{
    wynik -= p;
}



