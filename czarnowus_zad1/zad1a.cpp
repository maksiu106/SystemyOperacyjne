//K. Czarnowus, zad. 1(a), 19.03.2023

#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	std::cout << getuid() << " - UID" << std::endl;
	std::cout << getgid() << " - GID" << std::endl;
	std::cout << getpid() << " - PID (identyfikator procesu)" << std::endl;
	std::cout << getppid() << " - PPID (identyfikator procesu macierzystego)" << std::endl;
	std::cout << getpgrp() << " - PGID" << std::endl;
}
