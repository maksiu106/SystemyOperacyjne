//K. Czarnowus, 27.05.2023 r., program wykonujacy zadanie 9

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <iomanip>

#include "watki.hpp"

int licznik = 0;
int ilosc_sekcji;
pthread_mutex_t muteks;


void* funkcja_watkowa(void* argument)
{
	int* id_watku = (int*) argument;
	std::cout << "Uruchomiono watek o ID = " << id_watku << std::endl;

	for (int i=0; i<ilosc_sekcji; ++i)
	{
		//sekcja prywatna
		std::cout << "Watek o ID = " << id_watku << " wykonuje swoja sekcje prywatna po raz " << i+1 << std::endl;
		sleep(rand()%3); //czekanie 0-2 s
		//sekcja krytyczna
		zamknij_mutex(&muteks);
		int licznik_lokalny = licznik+1;
		std::cout << std::setw(30) << std::right << "Watek " << id_watku << " wykonuje swoja sekcje krytyczna po raz " << i+1 << std::endl;
		std::cout << std::setw(30) << std::right << "\t\t\tZwieksza wartosc licznika o 1. Teraz wynosi on " << licznik_lokalny << std::endl;
		sleep(rand()%3); //czekanie 0-2 s
		std::cout << std::setw(30) << std::right << "Watek " << id_watku << " opuszcza sekcje krytyczna" << std::endl;
		licznik = licznik_lokalny;
		//opuszcznie sekcji krytycznej
		otworz_mutex(&muteks);
	}
	return argument;
}

int main(int argc, char **argv) //1 argument - ilosc watkow, 2 - ilosc sekcji w kazdym watku
{
	srand(time(NULL));
	int ilosc_watkow = atoi(argv[1]);
	ilosc_sekcji = atoi(argv[2]);

	stworz_mutex(&muteks);
	std::cout << "Watek glowny stworzyl muteks" << std::endl;

	pthread_t id_watkow[ilosc_watkow];
	for (int i=0; i<ilosc_watkow; i++)
	{
		id_watkow[i]=i;
		pthread_create(&id_watkow[i], NULL, &funkcja_watkowa, (void *)id_watkow[i]); //tworzenie watkow
	}

	for (int i=0; i<ilosc_watkow; i++)
	{
		czekaj_na_watek(id_watkow[i]);
	}

	std::cout << "Zadania wykonywane przez wszystkie watki zostaly ukonczone." << std::endl;
	std::cout << "Wartosc licznika otrzymana: " << licznik << std::endl;
	std::cout << "Oczekiwana wartosc licznika: " << ilosc_watkow*ilosc_sekcji << std::endl;
}
