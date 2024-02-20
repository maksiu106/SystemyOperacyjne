//K. Czarnowus, 27.05.2023 r., plik z definicjami biblioteki z watkami

#include "watki.hpp"

void czekaj_na_watek(pthread_t id) //proces czeka na watek
{
	pthread_join(id, NULL);
}

int stworz_mutex(pthread_mutex_t* muteks) //argument to wskaznik na zadeklarowany wczesniej muteks
{
	return pthread_mutex_init(muteks, NULL); //tworzy muteks otwarty o
}

int zamknij_mutex(pthread_mutex_t* muteks)
{
	return pthread_mutex_lock(muteks);
}

int otworz_mutex(pthread_mutex_t* muteks)
{
	return pthread_mutex_unlock(muteks);
}

int usun_mutex(pthread_mutex_t* muteks)
{
	return pthread_mutex_destroy(muteks);
}
