//K. Czarnowus, zad. 1(d), 19.03.2023

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
	wypisz();
	for(int i=0; i<3; ++i) //trzykrotne stosowanie funkcji fork - powstanie w sumie 8 procesow
	{
		switch(fork())
		{
			case 0: {std::cout << "pokolenie procesow: " << (i+1) << std::endl; wypisz();}
			default: sleep(4);
		}
	}
	sleep(10); //wszystkie procesy czekaja - wszystkie zdaza sie wykonac
}
