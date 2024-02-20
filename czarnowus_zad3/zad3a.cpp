//Krzysztof Czarnowus, zad3a, 3.04.2023 r.

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void obslugasygnalu(int x)
{
	std::cout << "Proces " << getpid() << " wykonuje wlasnie wlasna obsluge sygnalu o numerze " << x << std::endl;
}

int main(int argc, char **argv) //pierwszy argument (1,2,3) to metoda obslugi sygnalu, druga to sygnal
{
	std::cout << "PID procesu: " << getpid() << std::endl;
	if (argc!=3) {std::cout << "Zle wprowadziles argumenty" << std::endl; exit(EXIT_FAILURE);} //sprawdza, czy wprowadzono dobra ilosc argumentow
	int numersygnalu = atoi(argv[2]);
	int metoda = atoi(argv[1]);
	switch (metoda)
	{
	case 1: {if (signal(numersygnalu, SIG_DFL) == SIG_ERR) exit(EXIT_FAILURE);}
	case 2: {if (signal(numersygnalu, SIG_IGN) == SIG_ERR) exit(EXIT_FAILURE);}
	case 3: {if (signal(numersygnalu, obslugasygnalu) == SIG_ERR) exit(EXIT_FAILURE);}
	}
	pause();
	exit(EXIT_SUCCESS);
}
