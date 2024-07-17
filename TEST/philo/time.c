#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_error("Time Failed\n");
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void ft_usleep(t_philo *philo, unsigned int ms)
{
    struct timeval start;
    struct timeval now;
    size_t elapsed;

    gettimeofday(&start, NULL);
    while (1)
    {
        gettimeofday(&now, NULL);
        elapsed = (now.tv_sec - start.tv_sec) * 1000
                + (now.tv_usec - start.tv_usec) / 1000;
        pthread_mutex_lock(&philo->info->death_check);
        if (elapsed >= ms || philo->info->dead != 0)
        {
            pthread_mutex_unlock(&philo->info->death_check);
            break;
        }
        pthread_mutex_unlock(&philo->info->death_check);
        usleep(400);  // Reduced sleep interval
    }
    return ;
}
