//K. Czarnowus, zad. 8, plik z definicjami, 26.05.2023

#include "kolejki.hpp"
#include <iostream>

mqd_t stworz_kolejke(const char* nazwa, struct mq_attr* atrybuty) //stworzenie kolejki
{
	mqd_t deskryptor = mq_open(nazwa, O_CREAT | O_EXCL | O_RDWR, 0644, NULL);
	return deskryptor;
}

mqd_t otworz_czytaj_kolejke(const char* nazwa)
{
	mqd_t deskryptor = mq_open(nazwa, O_RDONLY);
	return deskryptor;
}

mqd_t otworz_wpisuj_kolejke(const char* nazwa)
{
	mqd_t deskryptor = mq_open(nazwa, O_WRONLY);
	return deskryptor;
}

void wyslij_kolejka(mqd_t deskryptor, const char* wiadomosc, int rozmiar, int priorytet)
{
	mq_send(deskryptor, wiadomosc, rozmiar, priorytet);
}

void odbierz_z_kolejki(mqd_t deskryptor, char* bufor, size_t rozmiar)
{
	mq_receive(deskryptor, bufor, rozmiar, NULL);
}

void wyswietl_atrybuty(mqd_t deskryptor, struct mq_attr* atrybuty)
{
	mq_getattr(deskryptor, atrybuty);
}

void zamknij_kolejke(mqd_t deskryptor)
{
	mq_close(deskryptor);
}

void usun_kolejke(const char* nazwa)
{
	mq_unlink(nazwa);
}
