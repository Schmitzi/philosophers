#include "philo.h"

int	mutex_init(t_philo *philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&philo->info->write, NULL);
	pthread_mutex_init(&philo->info->death_check, NULL);
	while (i < philo->info->count)
	{
		pthread_mutex_init(&philo->info->forks[i], NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
	return (true);
}
