#include <iostream>
#include <cstdlib>

using namespace std;

struct polaczenie
{
    int miasto1;
    int miasto2;
    int waga;
    int przynaleznosc_do_drzewa=0;
    bool uzyte=0;

	polaczenie* nastepne;

};


int ilosc_miast=0, ilosc_polaczen=0, wybor;

polaczenie* start_listy;


void start();
void zapisywanie_polaczenia();
void generowanie_drzewa();
void porzadkowanie();
void tworzenie_polaczen();
void wypisywanie();


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
           }
}

void zapisywanie_polaczenia ()
{

	polaczenie* nowe =  new polaczenie;

    system("cls");

    cout<<"\n\n\n                           Polaczenia\n\n             Mozesz podac maksymalnie 500 polaczen! \n\n\n";
    cout<<"                Aktualnie podales "<<ilosc_polaczen<<" polaczen.\n\n\n";

    cout<<"                Podaj numer pierwszego miasta: ";
	cin >> nowe->miasto1;

	while (nowe->miasto1 <= 0 || nowe->miasto1 > ilosc_miast) {
		cout << "podaj poprawny numer miasta: ";
		cin >> nowe->miasto1;
	};

   cout<<"                 Podaj numer drugiego miasta: ";
    cin>> nowe->miasto2;

	while (nowe->miasto2 <= 0 || nowe->miasto2 > ilosc_miast) {
		cout << "podaj poprawny numer miasta: ";
		cin >> nowe->miasto2;
	};

    cout<<"                   Podaj wage polaczenia: ";
    cin>> nowe->waga;

	while (nowe->waga <= 0) {
		cout << "Podaj dodatnia wage: ";
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
    cout<<"\n\n               0)            Wyjscie\n";
    cin>>wybor;


	// powinnismy potem tak zrobic zeby nie laczyc 2 miast kilka razy

     switch(wybor)
           {
               case 0:  start();                      break;
               case 1:  zapisywanie_polaczenia ();    break;
           }

}
void generowanie_drzewa()
{
   porzadkowanie();
   tworzenie_polaczen();
   wypisywanie();
}

void porzadkowanie()
{
	
	polaczenie *node = start_listy;
	for (int l = 0; l < ilosc_polaczen; l++) {

		cout << "pol. " << l + 1 << "waga: " << node->waga << endl;
		node = node->nastepne;
	}
	system("pause");
    
}

struct drzewo {
	polaczenie* krawedzie;
	drzewo* nastepne_drzewo;
};

int przeszukaj_drzewo(polaczenie* krawedzie, polaczenie* aktualne) {
	
	// co zwraca:
	// 0 - nie znaleziono w drzewie wierzcholkow
	// 1 - znaleziono w drzewie jeden z wierzcholkow (moze da sie polaczyc z innym drzewem)
	// 2 - znaleziono w drzewie oba wierzcholki (nie dolaczaj)
	
	int pierwszy = aktualne->miasto1;
	int drugi = aktualne->miasto2;
	int ktory_znaleziono;
	polaczenie* przeszukaj = krawedzie;

	do {
	
		if (przeszukaj->miasto1 == pierwszy || przeszukaj->miasto2 == pierwszy) {
			if (ktory_znaleziono = 2) return 2;
			else ktory_znaleziono = 1;
		}
		else if (przeszukaj->miasto1 == drugi || przeszukaj->miasto2 == drugi) {
			if (ktory_znaleziono = 1) return 2;
			else ktory_znaleziono = 2;
		}
		else ktory_znaleziono = 0;

		przeszukaj = przeszukaj->nastepne;

	} while (przeszukaj != NULL);

	if (ktory_znaleziono == 1) return 1;
	else if (ktory_znaleziono == 2) return 1;
	else return 0;
}

int przeszukaj_las(drzewo* las, polaczenie* aktualne) {

	bool znaleziono; // sprawdza czy wczesniej znaleziono jakis wierzcholek w ktoryms poprzednim drzewie
	int i = 1;
	do {
		if (przeszukaj_drzewo(las->krawedzie, aktualne) == 2) return 2; //wyrzuc na smietnik
		else if (przeszukaj_drzewo(las->krawedzie, aktualne) == 1) {
			if (znaleziono) {
				aktualne->przynaleznosc_do_drzewa = i; //lacz drzewa i oraz i-1
				return i;
			}
			else {
				znaleziono = true;
				aktualne->przynaleznosc_do_drzewa = i;
				las = las->nastepne_drzewo;
			}
		}
		else las = las->nastepne_drzewo;
		i++;
		
	} while (las != NULL);

	if(znaleziono)
	//dolacz do drzewa i

	else //zrob nowe drzewo
}

void tworzenie_polaczen()
{
	polaczenie* aktualne = start_listy;
	start_listy = start_listy->nastepne;

	drzewo* las = new drzewo;
	
	las->nastepne_drzewo = NULL;
	las->krawedzie = aktualne;

	do {
		aktualne = start_listy;
		start_listy = start_listy->nastepne;

		if (przeszukaj_las(las, aktualne) == 0) {
		
		
		}
		else if () {}
		else {};


	} while (start_listy != NULL);
}

void wypisywanie()
{
    system("cls");

    cout<<"\n\n               LISTA:\n\n";
    cout<<"     NR  |  Miasto A  |  Miasto B  |  Waga;\n";
    cout<<"    ---------------------------------------\n";
    for(int i=0;i<ilosc_polaczen-1;i++)
    {
        //if(polaczenia[i].uzyte)
        {
         //  cout<<"     "<<i+1<<"   |      "<<polaczenia[i].miasto1<<"     |      "<<polaczenia[i].miasto2<<"     |    "<<polaczenia[i].waga<<endl;
        }

    }
}




