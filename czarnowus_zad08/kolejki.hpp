//K. Czarnowus, zad. 8, plik naglowkowy z deklaracjami, 26.05.2023

#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#define NAZWA_KS "/KolejkaSerwera"
#define ROZMIAR 100

#ifndef KOLEJKI_HPP_
#define KOLEJKI_HPP_

mqd_t stworz_kolejke(const char*, struct mq_attr*); //stworzenie kolejki
mqd_t otworz_czytaj_kolejke(const char*); //otwieranie kolejki w jednym z dwoch trybow
mqd_t otworz_wpisuj_kolejke(const char*);
void wyslij_kolejka(mqd_t, const char*, int, int); //do wysylania komunikatow
void odbierz_z_kolejki(mqd_t, char*, size_t); //do czytania komunikatow
void wyswietl_atrybuty(mqd_t, struct mq_attr*); //ogladanie atrybutow kolejki
void zamknij_kolejke(mqd_t); //zamykanie kolejki
void usun_kolejke(const char*); //usuwanie kolejki

#endif
