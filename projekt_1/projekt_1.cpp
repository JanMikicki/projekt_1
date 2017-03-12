#include <iostream>
#include <cstdlib>

using namespace std;

struct polaczenie
{
    int miasto1;
    int miasto2;
    int waga;
    int przynaleznosc_do_drzewa=0;


	polaczenie* nastepne;

};

struct drzewo {
	polaczenie* krawedzie;
	drzewo* nastepne_drzewo;
};

int ilosc_miast = 0;
int ilosc_polaczen = 0;
int wybor;

polaczenie* start_listy = NULL;
drzewo* las = new drzewo;

void start();
void zapisywanie_polaczenia();
void generowanie_drzewa();
void tworzenie_polaczen();
void wypisywanie();
int przeszukaj_las(drzewo*, polaczenie*, int &);
int przeszukaj_drzewo(polaczenie*, polaczenie*);


int main()
{
    cout<<"\n\n\n                      PLANOWANIE BUDOWY \n\n\n";
    cout<<"                     Podaj ilosc miast: ";
    cin>>ilosc_miast;

    start();

    return 0;
}


void start()
{
    system("cls");

    cout<<"\n\n\n                      PLANOWANIE BUDOWY ";
    cout<<"\n\n\n                   1) Dodawanie polaczenia.";
    cout<<"\n\n                   2)  Generowanie drzewa.\n";
    cin>>wybor;

    switch(wybor)
           {
               case 1:  zapisywanie_polaczenia ();         break;
               case 2:  generowanie_drzewa();              break;
               default: start();                           break;
           }
}

void zapisywanie_polaczenia ()
{

	polaczenie* nowe =  new polaczenie;

    system("cls");

    cout<<"\n\n                  Aktualnie podales "<<ilosc_polaczen<<" polaczen.\n\n\n";

	if (start_listy != NULL) {
		polaczenie* wyswietlaj = start_listy;
		cout << "                       Dodane polaczenia: \n" << endl;
		cout << "                    Miasto A" << " | " << "Miasto B" << " | Waga" << endl;
		cout << "                  -------------------------------"<< endl;
		do {
			cout << "                       " << wyswietlaj->miasto1 << "     |    " << wyswietlaj->miasto2 << "     |   " << wyswietlaj->waga << endl;
			wyswietlaj = wyswietlaj->nastepne;
		} while (wyswietlaj != NULL);
	}




    cout<<"\n                Podaj numer pierwszego miasta: ";
	cin >> nowe->miasto1;

	while (nowe->miasto1 <= 0 || nowe->miasto1 > ilosc_miast) {
		cout << "                 Podaj poprawny numer miasta: ";
		cin >> nowe->miasto1;
	};

   cout<<"                 Podaj numer drugiego miasta: ";
    cin>> nowe->miasto2;

	while (nowe->miasto2 <= 0 || nowe->miasto2 > ilosc_miast || nowe->miasto2 == nowe->miasto1) {
		cout << "                 Podaj poprawny numer miasta: ";
		cin >> nowe->miasto2;
	};

    cout<<"                   Podaj wage polaczenia: ";
    cin>> nowe->waga;

	while (nowe->waga <= 0) {
		cout << "                   Podaj dodatnia wage: ";
		cin >> nowe->waga;
	}

	if (ilosc_polaczen == 0) {
		start_listy = nowe;
		nowe->nastepne = NULL;
	}
	else if (start_listy->waga >= nowe->waga) {

		nowe->nastepne = start_listy;
		start_listy = nowe;

	}
	else {

		polaczenie* szukaj = start_listy;
		polaczenie* poprzedni;

		while (szukaj != NULL && szukaj->waga <= nowe->waga) {
			poprzedni = szukaj;
			szukaj = szukaj->nastepne;
		}
		nowe->nastepne = szukaj;
		poprzedni->nastepne = nowe;

	}


    ilosc_polaczen++;

    cout<<"\n\n\n               1)   Dodaj kolejne polaczenia";
    cout<<"\n\n               0)            Powrot\n";
    cin>>wybor;


	// powinnismy potem tak zrobic zeby nie laczyc 2 miast kilka razy

     switch(wybor)
           {
               case 0:  start();                      break;
               case 1:  zapisywanie_polaczenia ();    break;
               default: {
                            cout<<"          Podales zly numer!!!\n\n";
                            system("pause");
                             start();
                        }                           break;
           }

}

void generowanie_drzewa()
{
   tworzenie_polaczen();
   wypisywanie();
}


int przeszukaj_drzewo(polaczenie* krawedzie, polaczenie* aktualne) {

	// co zwraca:
	// 0 - nie znaleziono w drzewie wierzcholkow
	// 1 - znaleziono w drzewie jeden z wierzcholkow (moze da sie polaczyc z innym drzewem, a jesli nie to na koniec dolacz do tego gdzie znaleziono wierzcholek)
	// 2 - znaleziono w drzewie oba wierzcholki (nie dolaczaj)

	int pierwszy = aktualne->miasto1;
	int drugi = aktualne->miasto2;
	int ktory_znaleziono = 0;
	polaczenie* przeszukaj = krawedzie;

	do {

		if (przeszukaj->miasto1 == pierwszy || przeszukaj->miasto2 == pierwszy) {
			if (ktory_znaleziono == 2) return 2;
			else ktory_znaleziono = 1;
		}
		else if (przeszukaj->miasto1 == drugi || przeszukaj->miasto2 == drugi) {
			if (ktory_znaleziono == 1) return 2;
			else ktory_znaleziono = 2;
		}
		
		przeszukaj = przeszukaj->nastepne;

	} while (przeszukaj != NULL);

	if (ktory_znaleziono == 1) return 1;
	else if (ktory_znaleziono == 2) return 1;
	else return 0;
}

int przeszukaj_las(drzewo* las, polaczenie* aktualne, int &i) {

	// co zwraca:
	// 0 - nieprzydatna krawedz
	// 1 - dolacz do drzewa i
	// 2 - polacz drzewa i oraz i-1
	// 3 - zrob nowe drzewo

	drzewo* las_temp = las;
	bool znaleziono = false; // sprawdza czy wczesniej znaleziono jakis wierzcholek w ktoryms poprzednim drzewie

	do {

		int h = przeszukaj_drzewo(las_temp->krawedzie, aktualne);
		switch (h)
		{
		case 1: if (znaleziono) {
			//lacz drzewa i oraz aktualne->przynaleznosc
			return 2;
		}
				else {
					znaleziono = true;
					aktualne->przynaleznosc_do_drzewa = i;
					las_temp = las_temp->nastepne_drzewo;
				}
				break;

		case 2: return 0;

		default: las_temp = las_temp->nastepne_drzewo;
			break;
		}
		i++;
		
	} while (las_temp != NULL);

	if (znaleziono) //dolacz do drzewa
		return 1;

	else return 3;
}


void tworzenie_polaczen()
{
	polaczenie* aktualne = start_listy;
	start_listy = start_listy->nastepne;

	las->nastepne_drzewo = NULL;
	las->krawedzie = aktualne;
	aktualne->nastepne = NULL;

	do {
		aktualne = start_listy;
		start_listy = start_listy->nastepne;

		drzewo* przeszukuj_las = las;
		polaczenie* przeszukuj_drzewo;

		int i = 0;

		int r = przeszukaj_las(las, aktualne, i);

		switch (r)
		{

		case 0: delete aktualne; // niepotrzebna krawedz
			break;

		case 1: //dolacz do drzewa aktualne->przynaleznosc

			for (int j = 0; j < aktualne->przynaleznosc_do_drzewa; j++) {
				przeszukuj_las = przeszukuj_las->nastepne_drzewo;
			}
			przeszukuj_drzewo = przeszukuj_las->krawedzie;

			while (przeszukuj_drzewo->nastepne != NULL)
				przeszukuj_drzewo = przeszukuj_drzewo->nastepne;

			przeszukuj_drzewo->nastepne = aktualne;

			aktualne->nastepne = NULL;
			break;

		case 2: //polacz 2 drzewa (i oraz aktualne->przynaleznosc)

			drzewo* drzewo_do_polaczenia;

			for (int j = 0; j < aktualne->przynaleznosc_do_drzewa; j++) {
				przeszukuj_las = przeszukuj_las->nastepne_drzewo;
			}

			drzewo_do_polaczenia = przeszukuj_las;
			przeszukuj_drzewo = przeszukuj_las->krawedzie;

			while (przeszukuj_drzewo->nastepne != NULL)
				przeszukuj_drzewo = przeszukuj_drzewo->nastepne;

			przeszukuj_drzewo->nastepne = aktualne;
			przeszukuj_las = las;

			for (int j = 0; j < i; j++) {
				przeszukuj_las = przeszukuj_las->nastepne_drzewo;
			}

			aktualne->nastepne = przeszukuj_las->krawedzie;
			drzewo_do_polaczenia = drzewo_do_polaczenia->nastepne_drzewo;
			drzewo_do_polaczenia->nastepne_drzewo = przeszukuj_las->nastepne_drzewo;

			break;

		default: //zrob nowe drzewo i tam dolacz

			while (przeszukuj_las->nastepne_drzewo != NULL)
				przeszukuj_las = przeszukuj_las->nastepne_drzewo;

			przeszukuj_las->nastepne_drzewo = new drzewo;
			przeszukuj_las->nastepne_drzewo->nastepne_drzewo = NULL;
			przeszukuj_las->nastepne_drzewo->krawedzie = aktualne;

			aktualne->nastepne = NULL;
			break;
		}

	} while (start_listy != NULL);

}

void wypisywanie()
{
    system("cls");

    cout<<"\n\n               LISTA:\n\n";
    cout<<"    |  Miasto A  |  Miasto B  |  Waga\n";
    cout<<"    ---------------------------------------\n";


	while (las->krawedzie != NULL) {

		cout << "          " << las->krawedzie->miasto1 << "     |      " << las->krawedzie->miasto2 << "     |    " << las->krawedzie->waga << endl;

		las->krawedzie = las->krawedzie->nastepne;
	}

	cout << "\n\n";
	system("pause");

}




