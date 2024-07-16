#include "philo.h"
#include <complex.h>

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->info->write);
	time = get_time() - philo->info->begin;
	if (ft_strcmp("has died", str) == 0 && philo->info->dead == 0)
	{
		printf("%lu %ld %s\n", time, philo->id, str);
		philo->info->dead = 1;
	}
	if (!philo->info->dead)
		printf("%lu %ld %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}

void *monitor(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    while (philo->info->dead == 0)
    {
        pthread_mutex_lock(&philo->info->write);
        if (philo->info->finished >= philo->info->num_philo)
            philo->info->dead = 1;
        pthread_mutex_unlock(&philo->info->write);
        ft_usleep(1000);
    }
    return (void *)0;
}

void *routine(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    philo->til_death = philo->info->til_death + get_time();
    if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo) != 0)
    {
        free(philo);
        return (void *)1;
    }
    while (philo->info->dead == 0)
    {
        eat(philo);
        if (philo->info->dead == 0)
        {
            messages("is thinking", philo);
            ft_usleep(1000);
        }
    }
    if (pthread_join(philo->thread, NULL) != 0)
    {
        free(philo);
        return (void *)1;
    }
    return (void *)0;
}

void *supervisor(void *ptr)
{
    int meals;
    t_philo *philo;

    philo = (t_philo *)ptr;
    meals = 0;
    philo->eat = 0;
    while (philo->info->dead == 0)
    {
        pthread_mutex_lock(&philo->lock);
        if (get_time() >= philo->til_death && philo->eat == 0)
            messages("has died", philo);
        if (philo->num_meal == philo->info->num_meal && meals == 0)
        {
            philo->info->finished++;
            meals = 1;
        }
        pthread_mutex_unlock(&philo->lock);
        ft_usleep(1000);
    }
    return (void *)0;
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	messages("took left fork", philo);
	ft_usleep(1000);
	pthread_mutex_lock(philo->right_fork);
	messages("took right fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	messages("is sleeping", philo);
	ft_usleep(philo->info->sleep_dur * 1000);
}

void	eat(t_philo *philo)
{
	int64_t	time;

	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eat = 1;
	time = get_time();
	philo->til_death = time + philo->info->til_death;
	messages("is eating", philo);
	ft_usleep(philo->info->eat_dur * 1000);
	philo->num_meal++;
	philo->eat = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
	messages("is thinking", philo);
	ft_usleep(1000);
}
