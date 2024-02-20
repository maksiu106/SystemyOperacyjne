//Krzysztof Czarnowus, 22.05.2023 r., plik naglowkowy z definicjami funkcji do obslugi zadania 7

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "pamiecdzielona_lib.hpp"

int stworz_pd(const char* nazwa) //tworzy obiekt pamieci dzielonej
{
	int deskryptor = shm_open(nazwa, O_RDWR | O_CREAT | O_EXCL, 0644);
	return deskryptor;
}

int otworz_pd(const char* nazwa) //otworz obiekt pamieci dzielonej
{
	int deskryptor = shm_open(nazwa, O_RDWR, 0644);
	return deskryptor;
}

void rozmiar_pd(int deskryptor) //ustawianie rozmiaru pamieci dzielonej
{
	ftruncate(deskryptor, 1000); //ustawia pamiec 1000 bajtow
}

void* odwzoruj_pd(size_t rozmiar, int deskryptor) //mapowanie pamieci dzielonej do swojej przestrzeni
{
	void* adres = mmap(NULL, rozmiar, PROT_READ | PROT_WRITE, MAP_SHARED, deskryptor, 0);
	return adres;
}

void zamknij_pd(int deskryptor) //zamykanie obiektu pamieci dzielonej
{
	close(deskryptor);
}

void usun_pd(const char* nazwa) //usuwanie obiektu pamieci dzielonej
{
	shm_unlink(nazwa);
}
