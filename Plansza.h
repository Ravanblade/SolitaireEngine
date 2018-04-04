#pragma once
#include "LogikaGry.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include <sstream>
#include <vector>


using namespace std;

enum SLOT
{
	KOL_1 = 0,
	KOL_2 = 1,
	KOL_3 = 2,
	KOL_4 = 3,
	KOL_5 = 4,
	KOL_6 = 5,
	KOL_7 = 6,
	KOL_8 = 7,
	NEXT_1 = 8,
	NEXT_2 = 9,
	NEXT_3 = 10,
	NEXT_4 = 11,
	STOS = 12
};

enum STATUS
{
    MENU,
    GRA,
    AUTORZY,
    KONIEC
};

struct Punkt
{
	int x;
	int y;
};

class Plansza
{
public:
	Plansza(LogikaGry *g);
	~Plansza();

	void rysujMenu(bool przerysuj);
	void rysujGre(bool przerysuj);
	void rysujAutorzy(bool przerysuj);
	void koniecGry();
	void klawisze(unsigned char znak);
	STATUS status();
    template <typename T> string inttostr(T n);

private:
	void rysujKarte(SLOT slot, string text, int kolor);
	void rysujZnak(Punkt p, string text, int kolor);
	void rysujZnak(int ax, int ay, string text, int kolor);
	void zmienStatus(STATUS st);
	string parser(string str);
	string wczytajPlik(string nazwa);
	Punkt pozycjaKarty(SLOT slot);
	STATUS statusPlanszy;
	short int menuPos;
	short int planszaMenuPos;
	short int iloscOpcjiMenu;
	short int planszaPos;
	bool inMenu;
	LogikaGry *gra;

};

