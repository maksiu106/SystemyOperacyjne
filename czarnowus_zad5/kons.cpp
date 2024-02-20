//Krzysztof Czarnowus, program powiazany z zad5, 12.04.2023 r.

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ROZMIAROUT 10

int main(int argc, char **argv)
{
	int deskpliku = open(argv[1], O_WRONLY | O_CREAT, 0644); //otwarcie lub utworzenie pliku wyjsciowego
	int deskpotoku = open("potok", O_RDONLY, 0644); //otwarcie potoku nazwanego
	char towar[500];
	int status = read(deskpotoku, towar, ROZMIAROUT); //wczytanie 15 znakow z potoku
	while (status>0) //wpisywanie znakow do pliku
	{
		write(deskpliku, towar, status); //wpisanie danych do pliku
		std::cout << "Konsument przeczytal z potoku " << status << " znakow: " << std::flush;
		write(STDOUT_FILENO, towar, ROZMIAROUT); //wypisanie na wyjscie wczytanych z potoku znakow
		std::cout << std::endl;
		usleep(100000);
		status = read(deskpotoku, towar, ROZMIAROUT); //przeczytanie z potoku kolejnych znakow
	}
	close(deskpliku);
	close(deskpotoku);
}
