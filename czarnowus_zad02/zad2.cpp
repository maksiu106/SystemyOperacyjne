//K. Czarnowus, zad. 2, 19.03.2023

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	std::cout << "PROCESY POTOMNE\n" << std::endl;
	for(int i=0; i<3; ++i) //trzykrotne stosowanie funkcji fork - powstanie w sumie 8 procesow
	{
		switch(fork())
		{
			case 0: execl("./wypisz","wypisz", (char *) NULL);
			default: wait(0);//czekanie na pierwszy proces potomny; w efekcie czeka sie na wszystkie
		}
	}
	std::cout << "PROCES MACIERZYSTY\n" << std::endl;
	execl("./wypisz","wypisz", (char *) NULL);
}
