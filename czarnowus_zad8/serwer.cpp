//K. Czarnowus, zad. 8, program serwera, 26.05.2023

#include <iostream>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <string>

#include "kolejki.hpp"

mqd_t deskryptor_serw;

void zamykanie()
{
	zamknij_kolejke(deskryptor_serw);
	usun_kolejke(NAZWA_KS);
}

void zamykanie2(int x)
{
	usun_kolejke(NAZWA_KS);
	exit(1);
}

float kalkulator(float liczba1, float liczba2, char dzialanie)
{
	float wynik = 0;
	switch(dzialanie)
	{
	case '+': {wynik = liczba1+liczba2; return wynik;}
	case '-': {wynik = liczba1-liczba2; return wynik;}
	case '*': {wynik = liczba1*liczba2; return wynik;}
	case '/': {wynik = liczba1/liczba2; return wynik;}
	default: {std::cout << "Klient wyslal zly operator - wynik zostaje ustawiony domyslnie na 0" << std::endl;}
	return wynik;
	}
}

int main()
{
	signal(SIGINT, zamykanie2);
	atexit(zamykanie);
	srand(time(NULL)); //inicjalizowanie generatora liczb pseudolosowych

	struct mq_attr atrybuty; //tworzymy poczatkowe atrybuty kolejki, ktora otworzymy
	atrybuty.mq_flags = 0;
	atrybuty.mq_maxmsg = 20; //ilosc komunikatow
	atrybuty.mq_msgsize = ROZMIAR; //rozmiar wiadomosci
	atrybuty.mq_curmsgs = 0;

	stworz_kolejke(NAZWA_KS, &atrybuty);
	mqd_t deskryptor_serw = otworz_czytaj_kolejke(NAZWA_KS); //otwiera kolejke serweru w trybie do czytania
	wyswietl_atrybuty(deskryptor_serw, &atrybuty);
	std::cout << "Serwer uruchomil sie i stworzyl kolejke o nazwie " << NAZWA_KS << std::endl;
	std::cout << "Ma ona deskryptor: " << deskryptor_serw << std::endl;
	std::cout << "Ma ona flage " << atrybuty.mq_flags << ", maksymalna ilosc komunikatow " << atrybuty.mq_maxmsg << " oraz maksymalny rozmiar wiadomosci " << ROZMIAR << std::endl;

	while(1)
	{
		std::cout << "\nSerwer czeka na wiadomosc" << std::endl;
		char otrzymana_wiadomosc[ROZMIAR]; //bufor na wiadomosc
		odbierz_z_kolejki(deskryptor_serw, otrzymana_wiadomosc, atrybuty.mq_msgsize);
		int pid_klienta;
		float liczba1, liczba2;
		char dzialanie;
		sscanf(otrzymana_wiadomosc, "/%d %f%c%f", &pid_klienta, &liczba1, &dzialanie, &liczba2); //wpisanie z wiadomosci zmiennych

		std::string roboczy = "/"; //tworzenie nazwy kolejki klienta
		roboczy += std::to_string(pid_klienta);
		const char* nazwa_klienta = roboczy.c_str();

		float wynik = kalkulator(liczba1, liczba2, dzialanie); //policzenie wyniku i zapisanie jako const char*
		std::string rozwiazanie = std::to_string(wynik);
		const char* wiadomosc_powrotna = rozwiazanie.c_str();
		std::cout << "Serwer otrzymal wiadomosc: " << otrzymana_wiadomosc << std::flush;
		sleep(rand()%3); //czekanie 0-2 sekund
		std::cout << "Odpowiada na nia wynikiem, ktory wynosi " << atof(wiadomosc_powrotna) << std::endl;

		mqd_t deskryptor_klienta = otworz_wpisuj_kolejke(nazwa_klienta); //otwarcie kolejki klienta
		wyslij_kolejka(deskryptor_klienta, wiadomosc_powrotna, ROZMIAR, 0); //wysylanie wyniku kolejka
		zamknij_kolejke(deskryptor_klienta);
	}
}
