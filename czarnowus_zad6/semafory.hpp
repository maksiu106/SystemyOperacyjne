//Krzysztof Czarnowus, biblioteka operacji na semaforach - deklaracje, 14.05.2023 r.

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#ifndef SEMAFORY_HPP
#define SEMAFORY_HPP

sem_t* stworz_semafor(const char* nazwa); //tworzenie semafora nazwanego
void usun_semafor(const char* nazwa); //usuwanie semafora nazwanego
sem_t* otworz_semafor(const char* nazwa); //otwieranie semafora nazwanego
void zamknij_semafor(sem_t* adres); //zamykanie semafora nazwanego
int podnies(sem_t* adres); //podnoszenie wartosci semafora
int opusc(sem_t* adres); //opuszczanie wartosci semafora
int wartosc_semafora(sem_t* adres); //informacja o wartosci semafora

#endif
