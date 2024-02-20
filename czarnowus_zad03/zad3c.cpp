//Krzysztof Czarnowus, zad3c, 3.04.2023 r.

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	switch(pid_t potomnypid = fork())
	{
		case 0:
			setpgid(potomnypid,potomnypid); //ustawia proces potomny jako lidera grupy procesow
			execl("./zad3c2","zad3c2", argv[1], argv[2], NULL); //proces potomny uruchamia program zad3c2
		default:
			sleep(1);//czekanie, zeby procesy potomne zdazyly sie stworzyc
			kill(((-1)*potomnypid), atoi(argv[2])); //wyslanie zadanego sygnalu do wszystkich procesow z grupy
			wait(0);
	}
}
