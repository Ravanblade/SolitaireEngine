#include "Plansza.h"


Plansza::Plansza(LogikaGry *a)
: gra(a)
{
    menuPos = 0;
    planszaPos = 0;
    planszaMenuPos = 0;
    iloscOpcjiMenu = 2;
    inMenu = true;
    zmienStatus(MENU);
    rysujMenu(true);
}


Plansza::~Plansza()
{
}

string Plansza::wczytajPlik(string nazwa)
{
    ifstream plik;
    string odczyt;
    string s;
    plik.open(nazwa.c_str());

    if(plik.good())
    {
            while(!plik.eof())
            {
                getline(plik, s);
                odczyt += s + "\n";
            }

            plik.close(); // zamkniecie pliku
    }
    else
        cout << "Nie uda≥o siÍ odczytaÊ pliku!" << nazwa;

   return odczyt;
}

void Plansza::rysujMenu(bool przerysuj = false)
{
    if(przerysuj)
         rysujZnak(0,0, wczytajPlik("menu.txt"), 7);
       // cout << wczytajPlik("menu.txt");

   //17,10 18,10 19,10
    rysujZnak(29,17, "NOWA GRA", menuPos == 0 ? 13 : 7);
    rysujZnak(29,18, "AUTORZY", menuPos == 1 ? 13 : 7);
    rysujZnak(29,19, "WYJåCIE", menuPos == 2 ? 13 : 7);


}

void Plansza::rysujAutorzy(bool przerysuj = false)
{
   if(przerysuj)
        rysujZnak(0,0, wczytajPlik("autorzy.txt"), 7);
        rysujZnak(32,11, "Antonik Szymon", 2);
        rysujZnak(32,12, "Holisz Szymon", 2);
        rysujZnak(32,13, "Kochalski Jaros≥aw", 2);
        rysujZnak(38,15, "MENU", menuPos == 0 ? 13 : 7);
}

template <typename T>
string Plansza::inttostr(T n)
{
	stringstream s;
	s << n;
	return s.str();

}

void Plansza::rysujGre(bool przerysuj = false)
{

    if(przerysuj)
        rysujZnak(0,0, wczytajPlik("gra.txt"), 7);

    if(gra->pokazWynik() >= 2000)
    {
        zmienStatus(KONIEC);
        rysujZnak(0,0, "", 7);
        system("cls");
        rysujZnak(0,0, wczytajPlik("wygrana.txt"), 7);
        rysujZnak(15,6, inttostr(gra->pokazWynik()), 2);
        return;
    }
    else if(!gra->sprawdzOpcje())
    {
        zmienStatus(KONIEC);
        rysujZnak(0,0, "", 7);
        system("cls");
        rysujZnak(0,0, wczytajPlik("przegrana.txt"), 7);
        rysujZnak(15,6, inttostr(gra->pokazWynik()), 2);
        return;
    }

    rysujZnak(18,17, inttostr(gra->zwrocTalie(TAL_G)->iloscKart()), 7);

    rysujZnak(12,1, inttostr(gra->pokazWynik()), 7);

    for(int i = NEXT_1; i < NEXT_4+1; i++)
        if(gra->zwrocTalie(static_cast<RTalie>(planszaPos))->index(i-NEXT_1+2) != NULL)
            rysujKarte(static_cast<SLOT>(i), gra->zwrocTalie(static_cast<RTalie>(planszaPos))->index(i-NEXT_1+2)->nazwa +
                    " " + static_cast<char>(gra->zwrocTalie(static_cast<RTalie>(planszaPos))->index(i-NEXT_1+2)->kolor), 7);
        else
            rysujKarte(static_cast<SLOT>(i), "", 7);

    rysujKarte(STOS, gra->zwrocTalie(TAL_S)->index(1)->nazwa +
               " " + static_cast<char>(gra->zwrocTalie(TAL_S)->index(1)->kolor), 7);

    if(inMenu)
    {
        rysujZnak(3,22, "NastÍpna karta", planszaMenuPos == 0 ? 13 : 7);
        rysujZnak(3,23, "Menu", planszaMenuPos == 1 ? 13 : 7);

        for(int i = KOL_1; i < KOL_8+1; i++)
            if(gra->zwrocTalie(static_cast<RTalie>(i))->index(1) != NULL)
                rysujKarte(static_cast<SLOT>(i), gra->zwrocTalie(static_cast<RTalie>(i))->index(1)->nazwa +
                        " " + static_cast<char>(gra->zwrocTalie(static_cast<RTalie>(i))->index(1)->kolor), 7);
    }
    else
    {
        rysujZnak(3,22, "NastÍpna karta", 7);
        rysujZnak(3,23, "Menu", 7);

        for(int i = KOL_1; i < KOL_8+1; i++)
            if(gra->zwrocTalie(static_cast<RTalie>(i))->index(1) != NULL)
                rysujKarte(static_cast<SLOT>(i), gra->zwrocTalie(static_cast<RTalie>(i))->index(1)->nazwa +
                        " " + static_cast<char>(gra->zwrocTalie(static_cast<RTalie>(i))->index(1)->kolor), planszaPos == i ? 13 : 7);
            else
                rysujKarte(static_cast<SLOT>(i), "", planszaPos == i ? 13 : 7);
    }
}

void Plansza::rysujKarte(SLOT slot, string text, int kolor = -1)
{
    Punkt a = pozycjaKarty(slot);
    rysujZnak(a, wczytajPlik("karta.txt"), kolor);
    a.y += 1;
    a.x += 1;
    rysujZnak(a,text,kolor);

}

void Plansza::zmienStatus(STATUS st)
{
    this->statusPlanszy = st;
}

void Plansza::rysujZnak(Punkt p, string text, int kolor = -1)
{
    COORD coord = { p.x, p.y-1 };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );

    if(kolor >= 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolor);
    }

    stringstream str(text);
    string podzial;

    while (getline(str, podzial))
    {
       coord.Y++;
       SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
       cout << parser(podzial);
    }

    if(kolor >= 0)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void Plansza::rysujZnak(int ax, int ay, string text, int kolor = -1)
{
    Punkt a;
    a.x = ax;
    a.y = ay;
    rysujZnak(a, text, kolor);
}

Punkt Plansza::pozycjaKarty(SLOT slot)
{
	Punkt a;

    if(slot == KOL_1)
        a = {25, 4};
    else if(slot == KOL_2)
    {
        a.x = 35;
        a.y = 4;
    }
    else if(slot == KOL_3)
    {
        a.x = 45;
        a.y = 4;
    }
    else if(slot == KOL_4)
    {
        a.x = 55;
        a.y = 4;
    }
    else if(slot == KOL_5)
    {
        a.x = 25;
        a.y = 10;
    }
    else if(slot == KOL_6)
    {
        a.x = 35;
        a.y = 10;
    }
    else if(slot == KOL_7)
    {
        a.x = 45;
        a.y = 10;
    }
    else if(slot == KOL_8)
    {
        a.x = 55;
        a.y = 10;
    }
    else if(slot == NEXT_1)
    {
        a.x = 3;
        a.y = 4;
    }
    else if(slot == NEXT_2)
    {
        a.x = 3;
        a.y = 7;
    }
    else if(slot == NEXT_3)
    {
        a.x = 3;
        a.y = 10;
    }
    else if(slot == NEXT_4)
    {
        a.x = 3;
        a.y = 13;
    }
    else if(slot == STOS)
    {
        a.x = 3;
        a.y = 18;
    }
	return a;
}

void Plansza::koniecGry()
{
    zmienStatus(KONIEC);
}

STATUS Plansza::status()
{
    return this->statusPlanszy;
}

void Plansza::klawisze(unsigned char znak)
{
    switch(this->status())
    {
        case MENU:
        {

            //gora 38 dol 40 lewo 37 prawo 39 enter 13 escape 76

            if(znak == 72)
            {
               menuPos = menuPos == 0 ? 2 : menuPos-1;
               rysujMenu();
            }
            else if(znak == 80)
            {
               menuPos = menuPos == 2 ? 0 : menuPos+1;
               rysujMenu();
            }
            else if(znak == 13)
            {

                if(menuPos == 0)
                {
                  rysujZnak(0,0,"",-1); system("CLS");  zmienStatus(GRA); rysujGre(true);
                }
                else if(menuPos == 1)
                {
                  system("CLS");  zmienStatus(AUTORZY); rysujAutorzy(true);
                }
                else if(menuPos == 2)
                {
                  system("CLS"); exit( 0 );
                }
            }


            break;
        }


        case GRA:
        {

            if(inMenu)
            {

                if(znak == 72)
                    planszaMenuPos = planszaMenuPos == 0 ? iloscOpcjiMenu-1 : planszaMenuPos-1;

                else if(znak == 80)
                   planszaMenuPos = planszaMenuPos == iloscOpcjiMenu-1 ? 0 : planszaMenuPos+1;

                else if(znak == 77)
                {
                   inMenu = false;
                   planszaPos = 0;
                }
                else if(znak == 75)
                {
                    inMenu = false;
                    planszaPos = 7;
                }


                else if(znak == 13)
                {
                    if(planszaMenuPos == 0)
                        gra->nowaKarta();
                    else
                    {
                        system("CLS"); zmienStatus(MENU); rysujMenu(true);
                        break;
                    }


                }

            }
            else
            {

                if(znak == 72)
                   inMenu = true;

                else if(znak == 80)
                   inMenu = true;

                else if(znak == 77)
                    planszaPos = planszaPos == 7 ? 0 : planszaPos+1;

                else if(znak == 75)
                   planszaPos = planszaPos == 0 ? 7 : planszaPos-1;

                else if(znak == 13)
                {
                    if(gra->zwrocTalie(static_cast<RTalie>(planszaPos))->index(1) != NULL)
                        gra->polozKarteNaStos(static_cast<RTalie>(planszaPos));
                }

            }

            rysujGre();
            break;
        }

        case KONIEC:
        {
            system("CLS"); exit( 0 );

            break;
        }
        case AUTORZY:
        {

            if(znak == 13)
            {
                system("CLS");  zmienStatus(MENU); rysujMenu(true);
            }
            break;
        }

    }

}

string Plansza::parser(string str)
{
       for (int i = 0; i < str.length(); i++)
       {
               switch(str[i])
               {
                       case 'π':
                               str[i] = static_cast<char>(165);
                       break;

                       case 'Ê':
                               str[i] = static_cast<char>(134);
                       break;

                       case 'Í':
                               str[i] = static_cast<char>(169);
                       break;

                       case '≥':
                               str[i] = static_cast<char>(136);
                       break;

                       case 'Ò':
                               str[i] = static_cast<char>(228);
                       break;

                       case 'Û':
                               str[i] = static_cast<char>(162);
                       break;

                       case 'ú':
                               str[i] = static_cast<char>(152);
                       break;

                       case 'ü':
                               str[i] = static_cast<char>(171);
                       break;

                       case 'ø':
                               str[i] = static_cast<char>(190);
                       break;

                       case '•':
                               str[i] = static_cast<char>(164);
                       break;

                       case '∆':
                               str[i] = static_cast<char>(143);
                       break;

                       case ' ':
                               str[i] = static_cast<char>(168);
                       break;

                       case '£':
                               str[i] = static_cast<char>(157);
                       break;

                       case '—':
                               str[i] = static_cast<char>(227);
                       break;

                       case '”':
                               str[i] = static_cast<char>(224);
                       break;

                       case 'å':
                               str[i] = static_cast<char>(151);
                       break;

                       case 'è':
                               str[i] = static_cast<char>(141);
                       break;

                       case 'Ø':
                               str[i] = static_cast<char>(189);
                       break;
               }
       }
       return str;
}

