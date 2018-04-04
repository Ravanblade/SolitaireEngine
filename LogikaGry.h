#pragma once
#include "talia.h"

enum RTalie
{
    TAL_1 = 0,
    TAL_2 = 1,
    TAL_3 = 2,
    TAL_4 = 3,
    TAL_5 = 4,
    TAL_6 = 5,
    TAL_7 = 6,
    TAL_8 = 7,
    TAL_G = 8,
    TAL_S = 9,
    TAL_LAST = 10
};

class LogikaGry
{
    public:
        LogikaGry();
        virtual ~LogikaGry();
        Talia *zwrocTalie(RTalie rt);
        bool nowaKarta();
        bool sprawdzOpcje();
        bool polozKarteNaStos(RTalie a);
        bool szacuj(string st, string k);
        short int pokazWynik();

    protected:
        void utworzTalieKart();
        void rozdajKarty();
        void dodajPunkty(short int p);
        void odejmijPunkty(short int p);

    private:
        Talia *T[10];
        short int wynik;
};
