#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>

using namespace std;

struct Karta
{
	string nazwa;
	int kolor;
	Karta *next, *prev;
};

class Talia
{

public:
	Talia();
	~Talia();
	Karta *dodajNaPoczatek(Karta *a);
	Karta *dodajNaKoniec(Karta *a);
	Karta *wysunKarte();
	Karta *usunWybrana(Karta *a);
	Karta *index(int n);
	Karta *wstaw(Karta *a, Karta *b);
	void utworzTalie();
	void wyswietlTalie();
	void tasujTalie();
	int iloscKart();
	string nazwy(int index);
	int kolory(int index);

private:
	Karta *tail, *head;
	int ilosc;
	static const string nz[13];
	static const int kl[4];
};
