//K. Czarnowus, 4.06.2023 r., program wykonujacy zadanie 10

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <iomanip>

#include "watki.hpp"

#define MAXSIZE 30

int licznik = 0;
bool wybieranie[MAXSIZE];
int numer[MAXSIZE];

struct struktura
{
	int ilosc_sekcji;
	int ilosc_watkow;
	int id_watku;
};

int maksimum()
{
	int wartosc_najwieksza=0;
	for (int i=0; i<MAXSIZE; i++)
	{
		if (numer[i]>wartosc_najwieksza) {wartosc_najwieksza = numer[i];}
	}
	return wartosc_najwieksza;
}

void* funkcja_watkowa(void* argument)
{
	struct struktura* argumenty = (struct struktura*) argument;
	int id = argumenty->id_watku;
	int ilosc_sekcji = argumenty->ilosc_sekcji;
	int ilosc_watkow = argumenty->ilosc_watkow;
	std::cout << "Uruchomiono watek o ID = " << id << std::endl;

	for (int i=0; i<ilosc_sekcji; ++i)
	{
		//sekcja prywatna
		std::cout << "Watek o ID = " << id << " wykonuje swoja sekcje prywatna po raz " << i+1 << std::endl;
		sleep(rand()%3); //czekanie 0-2 s
		//algorytm piekarni - czekanie
		wybieranie[id] = true;
		numer[id] = maksimum()+1;
		wybieranie[id]=false;
		for (int j=0; j<ilosc_watkow; j++) //aktywne czekanie
		{
			while (wybieranie[j]);
			while (numer[j]!=0 && (numer[j]<numer[id] || ((numer[id]==numer[j]) && j<id)));
		}
		//sekcja krytyczna
		int licznik_lokalny = licznik+1;
		std::cout << std::setw(30) << std::right << "Watek " << id << " wykonuje swoja sekcje krytyczna po raz " << i+1 << std::endl;
		std::cout << std::setw(30) << std::right << "\t\t\tZwieksza wartosc licznika o 1. Teraz wynosi on " << licznik_lokalny << std::endl;
		sleep(rand()%3); //czekanie 0-2 s
		std::cout << std::setw(30) << std::right << "Watek " << id << " opuszcza sekcje krytyczna" << std::endl;
		licznik = licznik_lokalny;
		//opuszcznie sekcji krytycznej
		numer[id]=0;
	}
	return argument;
}

int main(int argc, char **argv) //1 argument - ilosc watkow, 2 - ilosc sekcji w kazdym watku
{
	srand(time(NULL));
	int ilosc_watkow = atoi(argv[1]);
	int ilosc_sekcji = atoi(argv[2]);

	for (int i=0; i<MAXSIZE; i++) {wybieranie[i]=false; numer[i]=0;} //wypelniam obie tablice false'em i zerami
	pthread_t id_watkow[ilosc_watkow];
	struct struktura argumenty[ilosc_watkow];
	for (int i=0; i<ilosc_watkow; i++)
	{
		argumenty[i].ilosc_sekcji = ilosc_sekcji;
		argumenty[i].ilosc_watkow = ilosc_watkow;
		argumenty[i].id_watku = i;
		id_watkow[i]=i;
		pthread_create(&id_watkow[i], NULL, &funkcja_watkowa, &argumenty[i]); //tworzenie watkow
	}

	for (int i=0; i<ilosc_watkow; i++)
	{
		czekaj_na_watek(id_watkow[i]);
	}

	std::cout << "Zadania wykonywane przez wszystkie watki zostaly ukonczone." << std::endl;
	std::cout << "Wartosc licznika otrzymana: " << licznik << std::endl;
	std::cout << "Oczekiwana wartosc licznika: " << ilosc_watkow*ilosc_sekcji << std::endl;
}
