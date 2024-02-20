//K. Czarnowus, zad. 8, program klienta, 26.05.2023

#include <iostream>
#include <signal.h>
#include <string>
#include <time.h>
#include <stdio.h>

#include "kolejki.hpp"

void zamykanie()
{
	int pid = getpid();
	std::string roboczy = "/";
	roboczy += std::to_string(pid);
	const char* nazwa = roboczy.c_str();
	usun_kolejke(nazwa);
}

void zamykanie2(int x)
{
	int pid = getpid(); //tworzenie nazwy kolejki
	std::string roboczy = "/";
	roboczy += std::to_string(pid);
	const char* nazwa = roboczy.c_str();
	usun_kolejke(nazwa);
	exit(1);
}

int main()
{
	signal(SIGINT, zamykanie2);
	atexit(zamykanie);
	srand(time(NULL)); //inicjalizowanie generatora liczb pseudolosowych

	struct mq_attr atrybuty2; //tworzymy poczatkowe atrybuty kolejki, ktora otworzymy
	atrybuty2.mq_flags = 0;
	atrybuty2.mq_maxmsg = 20; //ilosc komunikatow
	atrybuty2.mq_msgsize = ROZMIAR; //rozmiar wiadomosci
	atrybuty2.mq_curmsgs = 0;

	int pid = getpid(); //tworzenie nazwy kolejki
	std::string roboczy = "/";
	roboczy += std::to_string(pid);
	const char* kolejka = roboczy.c_str();
	std::cout << "Nazwa kolejki: " << kolejka << std::endl;

	mqd_t deskryptor_serw = otworz_wpisuj_kolejke(NAZWA_KS); //otwiera kolejka serwera w trybie do pisania
	stworz_kolejke(kolejka, &atrybuty2); //tworzy wlasna kolejke
	mqd_t deskryptor = otworz_czytaj_kolejke(kolejka); //otwiera wlasna w trybie do czytania
	wyswietl_atrybuty(deskryptor, &atrybuty2);
	std::cout << "Klient uruchomil sie i stworzyl kolejke o nazwie " << kolejka << std::endl;
	std::cout << "Ma ona deskryptor: " << deskryptor << std::endl;
	std::cout << "Ma ona flage " << atrybuty2.mq_flags << ", maksymalna ilosc komunikatow " << atrybuty2.mq_maxmsg << " oraz maksymalny rozmiar wiadomosci " << ROZMIAR << std::endl << std::endl;

	char wiadomosc[ROZMIAR];
	std::cout << "Wprowadz rownanie, ktore chcesz obliczyc; mozesz dodawac, odejmowac, mnozyc lub dzielic" << std::endl;
	while (fgets(wiadomosc, sizeof(wiadomosc), stdin)!=NULL)
	{
		std::string robocze = kolejka;
		robocze += " ";
		robocze += wiadomosc;
		const char* do_wyslania = robocze.c_str();
		wyslij_kolejka(deskryptor_serw, do_wyslania, ROZMIAR, 0);
		std::cout << "Klient wysyla do serwera wiadomosc o tresci: " << do_wyslania << std::flush;
		sleep(rand()%3); //czekanie 0-2 sekund

		char wynik[ROZMIAR];
		odbierz_z_kolejki(deskryptor, wynik, atrybuty2.mq_msgsize);
		double rozwiazanie = atof(wynik);
		std::cout << "Dla wprowadzonego dzialania klient otrzymal wynik " << rozwiazanie << std::endl;
		std::cout << "\nWprowadz nastepne rownanie; aby skonczyc, wprowadz ctrl+d" << std::endl;
	}
}
