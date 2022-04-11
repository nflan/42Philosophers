#include <stdio.h>
#include <stdlib.h>
#include "../include/philo.h"
#include <pthread.h>

pthread_mutex_t	lock;

void	*myfunct(void *arg)
{
	char	*msg;
	int		i;

	msg = (char *) arg;
	pthread_mutex_lock(&lock);
	for (i = 0; i < 10; i++)
	{
		printf("%s %d\n", msg, i);
	//	sleep(1);
	}
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	thread[atoi(av[1])];
	char		*msg1 = "First Thread";
	char		*msg2 = "Second Thread";
	int			ret[atoi(av[1])];
	int			i;

	pthread_mutex_lock(&lock);
	for (i = 0; i < atoi(av[1]); i++)
		ret[i] = pthread_create(&thread[i], NULL, myfunct, (void *) msg1);
	pthread_mutex_unlock(&lock);

	printf("Main funct after pthread create\n");

	for (i = 0; i < atoi(av[1]); i++)
	pthread_join(thread[i], NULL);

	for (i = 0; i < atoi(av[1]); i++)
	printf("%d Thread return %d\n", i, ret[i]);

	return (0);
}
