#include "talia.h"
#include "plansza.h"
#include "LogikaGry.h"
#include <conio.h>

int main()
{
	//gora 38 dol 40 lewo 37 prawo 39 enter 13 escape 76
	unsigned char znak;
	LogikaGry *gra = new LogikaGry();

	//for(int i = 0; i < 266; i++)
   //    cout << i << " " << char(i) << "\n";

//258-262 lub 3-6 kolory kart
//200 lewy dol
//201 lewy gora
//186 slupek
//187 prawy gora
//188 prawy dol
//205 poprzeczka

    Plansza *pl = new Plansza(gra);

	do
	{
		while (_kbhit())
		{
			znak = _getch();
            pl->klawisze(znak);
		}

	} while (znak != 27); //ESC

	system("PAUSE");
	return 0;
}

