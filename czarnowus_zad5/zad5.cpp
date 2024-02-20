//Krzysztof Czarnowus, zadanie 5a, 12.04.2023 r.

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void kasuj()
{
	unlink("potok"); //usuniecie potoku
}

int main(int argc, char **argv)
{
	mkfifo("potok", 0644); //utworzenie potoku nazwanego
	switch(fork()) //tworzenie producenta
	{
		case 0: execl("./prod", "prod", argv[1], NULL);
		default:;
	}
	switch(fork()) //tworzenie konsumenta
	{
		case 0: execl("./kons", "kons", argv[2], NULL);
		default:;
	}
	sleep(10);
	atexit(kasuj);
}
