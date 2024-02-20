//Krzysztof Czarnowus, program powiazany z programem zad4, 12.04.2023 r.

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>

#define ROZMIAROUT 10

int generator() //generuje liczbe losowa z zakresu 50 000 - 150 000
{
	return (100000 + (rand() % 100000));
}

int main(int argc, char **argv)
{
	std::cout << "Program bedacy konsumentem zostal uruchomiony" << std::endl;
	int czytaj= atoi(argv[2]); //konwersja argumentow (deskryptorow) na postac integer
	int wpisuj = atoi(argv[3]);
	sleep(0.5);
	close(wpisuj); //zamkniecie konca potoku sluzacego do wpisywania do niego wartosci
	int deskpliku = open(argv[1], O_WRONLY | O_CREAT, 0644); //otworzenie albo stworzenie pliku wyjsciowego
	char produkt[500];
	srand(time(NULL)); //zasiadnie seeda generatora losowych liczb
	int status = read(czytaj, produkt, ROZMIAROUT); //odczytanie znakow z potoku, zwrocenie ich ilosci
	while (status>0)
	{
		write(deskpliku, produkt, ROZMIAROUT); //zapisanie danych z potoku do pliku
		std::cout << "Konsument przeczytal z potoku " << status << " znakow: " << std::flush;
		write(STDOUT_FILENO, produkt, ROZMIAROUT); //wypisanie na wyjscie wczytanych z potoku znakow
		std::cout << std::endl;
		usleep(generator());
		status = read(czytaj, produkt, ROZMIAROUT); //wczytywanie z potoku kolejnych znakow
	}
	std::cout << "Konsument skonczyl przepisywanie danych do pliku wynikowego" << std::endl;
	close(czytaj);
	close(deskpliku);
}
