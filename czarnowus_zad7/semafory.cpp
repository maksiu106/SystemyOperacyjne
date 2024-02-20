//Krzysztof Czarnowus, biblioteka operacji na semaforach - definicje 14.05.2023 r.

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "semafory.hpp"

sem_t* stworz_semafor(const char* nazwa) //tworzenie semafora nazwanego
{
	sem_t* adres = sem_open(nazwa, O_CREAT|O_EXCL, 0644, 1); //tworzymy semafor
	if (adres == SEM_FAILED) {perror("Problem z utworzeniem semafora"); exit(-1);}
	return adres;
}

void usun_semafor(const char* nazwa) //usuwanie semafora nazwanego
{
	int info = sem_unlink(nazwa);
	if (info==-1) {perror("Problem z usunieciem semafora"); exit(-1);}
}

sem_t* otworz_semafor(const char* nazwa) //otwieranie semafora nazwanego
{
	sem_t* adres = sem_open(nazwa, 0);
	if (adres==SEM_FAILED) {perror("Problem z otworzeniem semafora"); exit(-1);}
	return adres;
}

void zamknij_semafor(sem_t* adres)
{
	int info = sem_close(adres);
	if (info==-1) {perror("Problem z zamknieciem semafora"); exit(-1);}
}

int podnies(sem_t* adres)
{
	int info = sem_post(adres);
	if (info==-1) {perror("Problem z podniesieniem semafora"); exit(-1);}
	return info;
}

int opusc(sem_t* adres)
{
	int info = sem_wait(adres);
	if (info==-1) {perror("Problem z opuszczeniem semafora"); exit(-1);}
	return info;
}

int wartosc_semafora(sem_t* adres)
{
	int wartosc;
	sem_getvalue(adres, &wartosc);
	if (wartosc==-1) {perror("Problem z odczytaniem wartosci semafora"); exit(-1);}
	return wartosc;
}
