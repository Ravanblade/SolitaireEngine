#include "talia.h"

const string Talia::nz[13] =
{
    "Król", "Dama", "Walet", "10",
	"9", "8", "7", "6", "5", "4", "3", "2", "AS"
};
const int Talia::kl[4] =
{
	259, 260, 261, 262
};

Talia::Talia()
{
	tail = NULL;
	head = NULL;
	ilosc = 0;
}

Talia::~Talia()
{
	Karta *a;

	while (head)
	{
		a = head->next;
		delete head;

		head = a;
	}
}

Karta *Talia::dodajNaPoczatek(Karta *a)
{
	a->next = head;
	a->prev = NULL;

	if (head)
		head->prev = a;

	head = a;

	if (!tail)
		tail = head;

	ilosc++;
	return head;
}


Karta *Talia::dodajNaKoniec(Karta *a)
{
	if (tail)
		tail->next = a;

	a->next = NULL;
	a->prev = tail;
	tail = a;

	if (!head)
		head = tail;

	ilosc++;
	return tail;
}

void Talia::utworzTalie()
{
	Karta *a;

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 4; j++)
		{
			a = new Karta;
			a->nazwa = nazwy(i);
			a->kolor = kolory(j);
			this->dodajNaPoczatek(a);

		}

}

Karta* Talia::index(int n)
{
	Karta* p;

	if ((!n) || (n > ilosc))
		return NULL;
	else if (n == ilosc)
		return tail;
	else if (n < ilosc / 2)
	{
		p = head;
		while (--n)
			p = p->next;

		return p;
	}
	else
	{
		p = tail;
		while (ilosc > n++)
			p = p->prev;

		return p;
	}
}

void Talia::wyswietlTalie()
{
	Karta * a;

	if (!head)
	{
		cout << "Brak kart." << endl;
	}
	else
	{
		a = head;
		while (a)
		{
			cout << a->nazwa << " " << a->kolor << "\n";

			a = a->next;
		}
	}
}

Karta *Talia::usunWybrana(Karta * a)
{
	if (a->prev)
		a->prev->next = a->next;
	else
		head = a->next;

	if (a->next)
		a->next->prev = a->prev;
	else
		tail = a->prev;

	ilosc--;
	return a;
}

Karta *Talia::wstaw(Karta *a, Karta *b)
{
	a->next = b->next; a->prev = b;
	b->next = a;

	if (a->next)
		a->next->prev = a;
	else
		tail = a;

	ilosc++;
	return a;
}

Karta *Talia::wysunKarte()
{
	Karta *a;

	if (head)
	{
		a = head;
		head = head->next;

		if (!head)
			tail = NULL;
		else
			head->prev = NULL;

		ilosc--;
		return a;
	}
	else return NULL;
}

void Talia::tasujTalie()
{
	srand(time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		Karta *a = this->wysunKarte();
		int losowy = rand() % ilosc + 1;
		Karta *b = this->index(losowy);

		this->wstaw(a, b);

	}
}

int Talia::iloscKart()
{
	return ilosc;
}

string Talia::nazwy(int index)
{
	return nz[index];
}

int Talia::kolory(int index)
{
	return kl[index];
}
