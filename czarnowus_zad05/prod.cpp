//Krzysztof Czarnowus, program powiazany z zad5, 12.04.2023 r.

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ROZMIARIN 15

int main(int argc, char **argv)
{
	int deskpliku = open(argv[1], O_RDONLY, 0644); //otwarcie pliku tekstowego
	int deskpotoku = open("potok", O_WRONLY, 0644); //otwarcie potoku nazwanego
	char towar[500];
	int status = read(deskpliku, towar, ROZMIARIN); //wczytanie 15 znakow z pliku
	while (status>0) //wpisywanie znakow do potoku nazwanego
	{
		write(deskpotoku, towar, status); //przeslanie danych do potoku
		std::cout << "Producent wpisal do potoku " << status << " znakow: " << std::flush;
		write(STDOUT_FILENO, towar, ROZMIARIN); //wypisanie na wyjscie tego, co wpisano wlasnie do potoku
		std::cout << std::endl;
		usleep(50000);
		status = read(deskpliku, towar, ROZMIARIN); //przeczytanie z pliku kolejnych znakow
	}
	close(deskpliku);
	close(deskpotoku);
}
