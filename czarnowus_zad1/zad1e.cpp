//K. Czarnowus, zad. 1(e), 19.03.2023

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

void wypisz() //funkcja wypisujaca wszystkie identyfikatory
{
	std::cout << getuid() << " - UID" << std::endl;
	std::cout << getgid() << " - GID" << std::endl;
	std::cout << getpid() << " - PID (identyfikator procesu)" << std::endl;
	std::cout << getppid() << " - PPID (identyfikator procesu macierzystego)" << std::endl;
	std::cout << getpgrp() << " - PGID\n" << std::endl;
}

int main()
{
	std::cout << "PIERWSZY WYWOLANY PROCES\n\n"; //wypisuje wszystkie identyfikatory pierwszego procesu
	wypisz();
	std::cout << "PROCESY POTOMNE\n" << std::endl;
	for(int i=0; i<3; ++i) //trzykrotne stosowanie funkcji fork - powstanie w sumie 8 procesow
	{
		switch(fork())
		{
			case 0: {setpgid((getpid()), (getpid())); wypisz();} //wypisanie wszystkich identyfikatorow dla kazego procesu potomnego
			default: wait(0); //czekanie na pierwszy proces potomny; w efekcie czeka sie na wszystkie
		}
	}
}
