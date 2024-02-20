//Krzysztof Czarnowus, zadanie 6, 14.05.2023 r.

#include <iostream>
#include <string>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "semafory.hpp"

void kasowanie(int x)
{
    usun_semafor("moj_semafor");
}

void kasowanie2()
{
    usun_semafor("moj_semafor");
}

//1 arg - nazwa procesu potomnego, 2 - liczba procesow potomnych, 3 - liczba sekcji krytycznych kazdego podprocesu
int main(int argc, char *argv[])
{
	signal(SIGINT, kasowanie);
	atexit(kasowanie2);
	sem_t* adres = stworz_semafor("moj_semafor");
	std::cout << "Utworzono semafor nazwany 'moj_semafor' o adresie " << adres << " i poczatkowej wartosci " << wartosc_semafora(adres) << std::endl;
	int deskryptorpliku = open("plik.txt", O_WRONLY | O_CREAT, 0644); //otwarcie lub stworzenie pliku z liczba
	write(deskryptorpliku, "0", 1); //wpisanie jednego bajta danych (liczby 0) do pliku
	close(deskryptorpliku); //zamkniecie pliku

	//tworzenie argumentu do przekazania do procesow potomnych
	std::string pomoc = "./";
	pomoc += argv[1];
	const char* sciezka = pomoc.c_str();

	int ilosc_dzieci = atoi(argv[2]);
	int potomkowie[ilosc_dzieci]; //tu bedziemy zbierac PID procesow potomnych, zeby potem na nie poczekac
	for (int i=0; i<ilosc_dzieci; ++i)
	{
		switch(potomkowie[i]=fork())
		{
		case 0: execl(sciezka, argv[1], argv[3], NULL); //uruchomienie procesow potomnych
		default:;
		}
	}
	sleep(1); //czekanie az procesy potomne sie uruchomia
	for (int i=0; i<ilosc_dzieci; ++i)
	{
		int status; //zmienna informuje o statusie procesu potomnego
		waitpid(potomkowie[i], &status, 0);
	}

	char wynik[10]; //tablica na wynik
	deskryptorpliku = open("plik.txt", O_RDONLY, 0644);
	read(deskryptorpliku, wynik, 10);
	close(deskryptorpliku);
	std::cout << "Dla zadanych parametrow liczba powinna wynosic " << atoi(argv[2])*atoi(argv[3]) << "\nOdczytana z pliku wartosc wynosi " << wynik << std::endl;
	remove("plik.txt");
}
