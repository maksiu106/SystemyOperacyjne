//Krzysztof Czarnowus, zad3c, 3.04.2023 r.
//program powiazany z programem zad3c

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
	switch (atoi(argv[1])) //ten proces zignoruje wszystkie sygnaly
	{
		case 1: {if (signal(atoi(argv[2]), SIG_IGN) == SIG_ERR) exit(EXIT_FAILURE);}
		case 2: {if (signal(atoi(argv[2]), SIG_IGN) == SIG_ERR) exit(EXIT_FAILURE);}
		case 3: {if (signal(atoi(argv[2]), SIG_IGN) == SIG_ERR) exit(EXIT_FAILURE);}
	}
	int i;
	int tablicapid[5];
	for (i=0; i<5; ++i)
	{
		switch(tablicapid[i]=fork())
		{
			case 0: execl("./zad3a","zad3a", argv[1], argv[2], NULL);
			default:;
		}
	}
	for (i=0; i<5; ++i)
	{
		sleep(1); //czekanie, zeby proces potomny zdazyl sie uruchomic
		int status; //zmienna informuje o statusie procesu potomnego
		waitpid(tablicapid[i], &status, 0);
		std::cout << "Proces potomny o PID " << tablicapid[i] << " zostal zakonczony ze statusem " << WEXITSTATUS(status) << std::endl;
		if (WIFSIGNALED(status)==1) //jesli proces zostal zakonczony przez sygnal
		{
			std::cout << "Zakonczyl go sygnal o kodzie: " << WTERMSIG(status) << " i nazwie " << strsignal(WTERMSIG(status)) << std::endl;
		}
	}
}
