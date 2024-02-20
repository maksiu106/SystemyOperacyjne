//Krzysztof Czarnowus, 22.05.2023 r., glowny program do wykonania zadania 7

#include <iostream>
#include <signal.h>
#include <sys/wait.h>

#include "pamiecdzielona_lib.hpp"
#include "semafory.hpp"

#define NELE 20
#define NBUF 5

void kasuj()
{
	usun_semafor("sem_prod");
	usun_semafor("sem_kons");
	usun_pd("pamiec_dzielona");
}

void kasuj2(int x)
{
	usun_semafor("sem_prod");
	usun_semafor("sem_kons");
	usun_pd("pamiec_dzielona");
}

//1 argument - nazwa pliku wejsciowego, 2 - nazwa pliku wyjsciowego
int main(int argc, char *argv[])
{
	atexit(kasuj);
	signal(SIGINT, kasuj2);
	sem_t* sem_prod = stworz_semafor("sem_prod");
	sem_t* sem_kons = stworz_semafor("sem_kons");
	opusc(sem_kons);
	for (int i=0; i<(NBUF-1); ++i) podnies(sem_prod); //podniesienie semafora producenta do wartosci rownej ilosci buforow
	int deskryptor_pd = stworz_pd("pamiec_dzielona");
	rozmiar_pd(deskryptor_pd); //ustawen
	std::cout << "Stworzono semafor producenta o adresie " << sem_prod << " i wartosci poczatkowej " << wartosc_semafora(sem_prod) << std::endl;
	std::cout << "Stworzono semafor konsumenta o adresie " << sem_kons << " i wartosci poczatkowej " << wartosc_semafora(sem_kons) << std::endl;
	std::cout << "Stworzono pamiec dzielona o deskryptorze " << deskryptor_pd << " oraz domyslnej pamieci " << sizeof(deskryptor_pd) << " bajtow" << std::endl;

	int dzieci[2]; //tablica na PID procesow potomnych
	switch(dzieci[0]=fork()) //otwieranie producenta
	{
	case 0: execl("./producent", "producent", argv[1], "sem_prod", "sem_kons", "pamiec_dzielona", NULL);
	default:;
	}

	switch(dzieci[1]=fork())
	{
	case 0: execl("./konsument", "konsument", argv[2], "sem_prod", "sem_kons", "pamiec_dzielona", NULL);
	default:;
	}

	sleep(1); //czekanie az procesy potomne sie uruchomia
	for (int i=0; i<2; i++)
	{
		int status; //zmienna informuje o statusie procesu potomnego
		waitpid(dzieci[i], &status, 0);
	}
}
