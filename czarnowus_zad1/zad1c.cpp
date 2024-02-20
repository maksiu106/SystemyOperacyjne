//K. Czarnowus, zad. 1(c), 19.03.2023

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
		std::cout << "\n" << std::endl;
		switch(fork())
		{
			case 0: {wypisz(); sleep(10);}
			default:;
		}
	}
}
