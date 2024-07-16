#include "philo.h"

int	mutex_init(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->num_philo)
	{
		pthread_mutex_init(&philo->info->forks[i], NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
	pthread_mutex_init(&philo->info->write, NULL);
	pthread_mutex_init(&philo->info->died, NULL);
	return (true);
}
