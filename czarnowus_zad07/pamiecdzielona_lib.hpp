//Krzysztof Czarnowus, 22.05.2023 r., plik naglowkowy z deklaracjami funkcji do obslugi zadania 7

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#ifndef PAMIECDZIELONA_LIB_HPP_
#define PAMIECDZIELONA_LIB_HPP_

int stworz_pd(const char*); //stworz obiekt pamieci dzielonej
int otworz_pd(const char*); //otworz obiekt pamieci dzielonej
void rozmiar_pd(int); //ustawianie rozmiaru pamieci dzielonej
void* odwzoruj_pd(size_t, int); //mapowanie pamieci dzielonej do swojej przestrzeni
void zamknij_pd(int); //zamykanie obiektu pamieci dzielonej
void usun_pd(const char*); //usuwanie obiektu pamieci dzielonej

#endif /* PAMIECDZIELONA_LIB_HPP_ */
