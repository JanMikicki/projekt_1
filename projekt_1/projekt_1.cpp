#include <iostream>
#include <cstdlib>

using namespace std;

struct polaczenia
{
    int miasto1;
    int miasto2;
    int waga;
    int przynaleznosc_do_drzewa=0;
    bool uzyte=0;
};

const int MAX_N=500;
int ilosc_miast=0, ilosc_polaczen=0, wybor;
polaczenia polaczenie[MAX_N];



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
    system("cls");

    cout<<"\n\n\n                           Polaczenia\n\n             Mozesz podac maksymalnie 500 polaczen! \n\n\n";
    cout<<"                Aktualnie podales "<<ilosc_polaczen<<" polaczen.\n\n\n";

    cout<<"                Podaj numer pierwszego miasta: ";
    cin>>polaczenie[ilosc_polaczen].miasto1;

   cout<<"                 Podaj numer drugiego miasta: ";
    cin>>polaczenie[ilosc_polaczen].miasto2;

    cout<<"                   Podaj wage polaczenia: ";
    cin>>polaczenie[ilosc_polaczen].waga;

    ilosc_polaczen++;

    cout<<"\n\n\n               1)   Dodaj kolejne polaczenie";
    cout<<"\n\n               0)            Wyjscie\n";
    cin>>wybor;

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
    ;
}

void tworzenie_polaczen()
{
    ;
}

void wypisywanie()
{
    system("cls");

    cout<<"\n\n               LISTA:\n\n";
    cout<<"     NR  |  Miasto A  |  Miasto B  |  Waga;\n";
    cout<<"    ---------------------------------------\n";
    for(int i=0;i<ilosc_polaczen-1;i++)
    {
        if(polaczenie[i].uzyte)
        {
           cout<<"     "<<i+1<<"   |      "<<polaczenie[i].miasto1<<"     |      "<<polaczenie[i].miasto2<<"     |    "<<polaczenie[i].waga<<endl;
        }

    }
}




