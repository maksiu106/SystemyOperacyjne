//Krzysztof Czarnowus, 22.05.2023 r., program powiazany z zadaniem 7

#include <iostream>
#include <sys/wait.h>

#include "pamiecdzielona_lib.hpp"
#include "semafory.hpp"

#define NELE 20
#define NBUF 5

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw=0, wyjmij=0;
} SegmentPD;

int sprawdz_koniec(SegmentPD wpd, int numer_buforu, int *koniec) //ma zmieniac zmienna koniec globalnie
{
	int i;
	for (i=0; i<NELE; i++)
	{
		if (wpd.bufor[numer_buforu][i]=='\0') {*koniec=i; return 0;} //zwraca 0 jesli w buforze jest koniec pliku
	}
	return 1; //zwraca 1 jesli w buforze nie ma konca pliku
}

//1 - nazwa pliku wyjsciowego, 2 - nazwa semafora producenta, 3 - nazwa semafora konsumenta, 4 - nazwa pamieci dzielonej
int main(int argc, char *argv[])
{
	int deskryptor_pliku = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	sem_t* sem_prod = otworz_semafor(argv[2]);
	sem_t* sem_kons = otworz_semafor(argv[3]);
	int deskryptor_pd = otworz_pd(argv[4]);
	SegmentPD* wpd = (SegmentPD*)odwzoruj_pd(sizeof(SegmentPD), deskryptor_pd);
	std::cout << "Uruchomiono proces konsumenta o PID = " << getpid() << ". Adres semaforu producenta: " << sem_prod << ", adres semaforu konsumenta: " << sem_kons << ", deskryptor pamieci dzielonej: " << deskryptor_pd << std::endl;
	int bajty = NELE, koniec, pomocniczy;
	do
	{
		opusc(sem_kons);
		if(sprawdz_koniec(*wpd, wpd->wyjmij, &koniec)!=1) bajty = write(deskryptor_pliku, wpd->bufor[wpd->wyjmij], koniec);
		else bajty = write(deskryptor_pliku, wpd->bufor[wpd->wyjmij], NELE);
		std::cout << "Konsumnt odczytal z bufora " << bajty << " bajtow danych" << std::endl;
		std::cout << "\tMaja one tresc: " << std::flush;
		write(STDOUT_FILENO, wpd->bufor[wpd->wyjmij], bajty);
		std::cout << "\n\tWartosc semafora producenta: " << wartosc_semafora(sem_prod) << std::endl;
		std::cout << "\tWartosc semafora konsumenta: " << wartosc_semafora(sem_kons) << std::endl;
		pomocniczy = wpd->wyjmij;
		wpd->wyjmij = (wpd->wyjmij+1)%NBUF; //zwiekszenie indeksu wyjmowania
		podnies(sem_prod);

	} while (sprawdz_koniec(*wpd, pomocniczy, &koniec)==1);
	close(deskryptor_pliku);
	zamknij_semafor(sem_prod);
	zamknij_semafor(sem_kons);
	zamknij_pd(deskryptor_pd);
}


