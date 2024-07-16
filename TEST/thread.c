#include "philo.h"

static void	destroy_mutex(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->num_philo && philo[i].state == 2)
	{
		pthread_mutex_destroy(&philo->info->forks[i]);
		pthread_mutex_destroy(&philo[i].lock);
		i++;
	}
	pthread_mutex_destroy(&philo->info->write);
	pthread_mutex_destroy(&philo->info->died);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	thread[MAX];
	pthread_t   make;

	i = -1;
	while (++i < philo->info->num_philo)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
			philo[i].state = 2;
			destroy_mutex(philo);
			pthread_mutex_unlock(&philo[i].lock);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
	}
	if (pthread_create(&make, NULL, &monitor, philo) != 0)
		return (destroy_mutex(philo), 1);
	i = 0;
	pthread_join(make, NULL);
	while (i < philo->info->num_philo && philo[i].state != 2)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (destroy_mutex(philo), 1);
		i++;
	}
	return (0);
}
