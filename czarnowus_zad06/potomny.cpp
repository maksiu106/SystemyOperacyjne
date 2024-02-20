//Krzysztof Czarnowus, program powiazany z zadaniem 6, 14.05.2023 r.

#include <iostream>
#include <string>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>

#include "semafory.hpp"

void sekcja_krytyczna()
{
	int deskryptorpliku = open("plik.txt", O_RDONLY, 0644);
	char numer[10];
	read(deskryptorpliku, numer, 10); //odczytanie liczby z pliku w opcji tylko do odczytu
	std::cout << "\tUruchomienie sekcji krytycznej przez proces o PID = " << getpid() << ". Liczba w pliku wynosi poczatkowo " << atoi(numer) << std::endl;
	close(deskryptorpliku);
	int liczba = atoi(numer)+1; //odczytanie liczby i zwiekszenie jej
	char nowa_liczba[10];
	sprintf(nowa_liczba, "%d", liczba);
	sleep((rand()%3)); //czekanie 0-3 sekundy
	std::cout << "\tZmieniono liczbe w pliku na " << nowa_liczba << std::endl;
	deskryptorpliku = open("plik.txt", O_WRONLY, 0644);
	write(deskryptorpliku, nowa_liczba, 10);
	close(deskryptorpliku);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	sem_t* adres = otworz_semafor("moj_semafor");
	int liczba_powtorzen = atoi(argv[1]);

	for (int i=0; i<liczba_powtorzen; ++i)
	{
		//wlasne sprawy
		sleep((rand()%3));
		opusc(adres);
		std::cout << "Proces " << getpid() << " zajmuje semafor i wykonuje powtorzenie sekcji krytycznej numer " << i+1 << std::endl;
		std::cout << "Proces " << getpid() << " wykonuje powtorzenie sekcji krytycznej numer " << i+1 << std::endl;
		//sekcja krytyczna
		sekcja_krytyczna();
		std::cout << "Proces " << getpid() << " zwalnia semafor" << std::endl;
		//reszta
		podnies(adres);
	}
}
