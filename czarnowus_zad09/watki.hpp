//K. Czarnowus, 27.05.2023 r., plik naglowkowy biblioteki z watkami


#ifndef WATKI_HPP_
#define WATKI_HPP_

#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <pthread.h>

void czekaj_na_watek(pthread_t);
int stworz_mutex(pthread_mutex_t*);
int zamknij_mutex(pthread_mutex_t*);
int otworz_mutex(pthread_mutex_t*);
int usun_mutex(pthread_mutex_t*);

#endif
