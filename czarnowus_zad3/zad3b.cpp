//Krzysztof Czarnowus, zad3b, 3.04.2023 r.

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
	extern const char * const sys_syglist[];
	switch(pid_t potomnypid = fork())
	{
		case 0: execl("./zad3a","zad3a", argv[1], argv[2], NULL); //proces potomny uruchamia program zad1a
		default:
		{
			sleep(1); //czekanie, zeby proces potomny zdazyl sie uruchomic
			if (kill(potomnypid, 0)==-1) {std::cout << "proces potomny nie istnieje" << std::endl; exit(EXIT_FAILURE);} //sprawdzanie, czy proces potomny powstal
			kill(potomnypid, atoi(argv[2])); //wyslanie zadanego sygnalu do procesu potomnego
			int status; //zmienna informuje o statusie procesu potomnego
			waitpid(potomnypid, &status, 0);
			std::cout << "Proces potomny o PID " << potomnypid << " zostal zakonczony ze statusem " << WEXITSTATUS(status) << std::endl;
			if (WIFSIGNALED(status)==1) //jesli proces zostal zakonczony przez sygnal
			{
				std::cout << "Zakonczyl go sygnal o kodzie: " << WTERMSIG(status) << " i nazwie " << strsignal(WTERMSIG(status)) << std::endl;
			}
		}
	}
}
