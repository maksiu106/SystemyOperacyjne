//Krzysztof Czarnowus, zadanie 4, 12.04.2023 r.

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <random>
#include <sys/wait.h>

#define ROZMIARIN 15

int generator() //generuje liczbe losowa z zakresu 50 000 - 100 000
{
	return (50000 + (rand() % 50000));
}

int main(int argc, char **argv) //pierwszy argument to plik wejsciowy, drugi to plik wyjsciowy
{
	int deskryptor[2];
	pipe(deskryptor); //utworzenie potoku nienazwanego
	std::cout << "Utworzono potok nienazwany" << std::endl;
	char czytaj[10]; //konwersja deskryptorow na format, ktory umozliwi przekazanie ich do konsumenta
	sprintf(czytaj, "%d", deskryptor[0]);
	char wpisuj[10];
	sprintf(wpisuj, "%d", deskryptor[1]);
	switch(fork()) //utworzenie procesu potomnego, ktory bedzie konsumentem
	{
	    case 0: execl("./konsument", "konsument", argv[2], czytaj, wpisuj, NULL);
	    default:;
	}
	int deskpliku = open(argv[1], O_RDONLY, 0644); //otwarcie pliku tekstowego
	close(deskryptor[0]); //zamkniecie konca potoku sluzacego do oczytywania z niego znakow
	char produkt[500];
	int status = read(deskpliku, produkt, ROZMIARIN); //odczytanie z pliku znakow i zwrocenie ich ilosci
	std::cout << "Wczytujemy plik" << std::endl;
	srand(time(NULL)); //zasiadnie seeda generatora losowych liczb
	while (status>0)
	{
		write(deskryptor[1], produkt, status); //przeslanie danych do potoku
		std::cout << "Producent wpisal do potoku " << status << " znakow: " << std::flush;
		write(STDOUT_FILENO, produkt, ROZMIARIN); //wypisanie na wyjscie tego, co wpisano wlasnie do potoku
		std::cout << std::endl;
		usleep(generator());
		status = read(deskpliku, produkt, ROZMIARIN); //przeczytanie z pliku kolejnych znakow
	}
	std::cout << "Producent przeslal wszystko do potoku" << std::endl;
	close(deskryptor[1]);
	close(deskpliku);
	wait(0);
}
