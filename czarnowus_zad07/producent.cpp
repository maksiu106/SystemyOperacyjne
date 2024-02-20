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

//1 - nazwa pliku wejsciowego, 2 - nazwa semafora producenta, 3 - nazwa semafora konsumenta, 4 - nazwa pamieci dzielonej
int main(int argc, char *argv[])
{
	std::cout << "Producent dziala" << std::endl;
	int deskryptor_pliku = open(argv[1], O_RDONLY, 0644);
	sem_t* sem_prod = otworz_semafor(argv[2]);
	sem_t* sem_kons = otworz_semafor(argv[3]);
	int deskryptor_pd = otworz_pd(argv[4]);
	SegmentPD* wpd = (SegmentPD*)odwzoruj_pd(sizeof(SegmentPD), deskryptor_pd);
	std::cout << "Uruchomiono proces producenta o PID = " << getpid() << ". Adres semaforu producenta: " << sem_prod << ", adres semaforu konsumenta: " << sem_kons << ", deskryptor pamieci dzielonej: " << deskryptor_pd << std::endl;

	int bajty = NELE; //wczytywanie z pliku, wrzucanie do pamieci dzielonej
	while(bajty == NELE)
	{
		opusc(sem_prod); //opuszczanie semaforu producenta
		bajty = read(deskryptor_pliku, wpd->bufor[wpd->wstaw], NELE); //czytanie pliku i wstawianie do buforu, zwracanie ilosci przeczytanych bajtow
		if (bajty!=NELE) wpd->bufor[wpd->wstaw][bajty] = '\0'; //jesli skonczyl sie plik, dodajemy do buforu znak konca
		std::cout << "Producent wstawil do bufora " << bajty << " bajtow danych" << std::endl;
		std::cout << "\tMaja one tresc: " << std::flush;
		write(STDOUT_FILENO, wpd->bufor[wpd->wstaw], bajty);
		std::cout << "\n\tWartosc semafora producenta: " << wartosc_semafora(sem_prod) << std::endl;
		std::cout << "\tWartosc semafora konsumenta: " << wartosc_semafora(sem_kons) << std::endl;
		wpd->wstaw = (wpd->wstaw+1)%NBUF; //zwiekszenie ideksu wstawiania
		podnies(sem_kons); //podniesienie semaforu konsumenta
	}
	close(deskryptor_pliku);
	zamknij_semafor(sem_prod);
	zamknij_semafor(sem_kons);
	zamknij_pd(deskryptor_pd);
}
