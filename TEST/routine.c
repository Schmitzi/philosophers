#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <complex.h>
#include <pthread.h>
#include <sys/time.h>

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;
	struct timeval tv;

	pthread_mutex_lock(&philo->info->death_check);
		if (philo->info->dead != 1)
		{
    		if (gettimeofday(&tv, NULL) != 0)
            {
    		   ft_putstr_fd("Failed: time", 2);
                return ;
            }
    		time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->info->begin;
			printf("%zu\t%zu %s\n", time, philo->id, str);
			pthread_mutex_unlock(&philo->info->death_check);
			return ;
		}
		pthread_mutex_unlock(&philo->info->death_check);
}

void *monitor(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    while (1)
    {
        pthread_mutex_lock(&philo->info->write);
        if (philo->info->end >= philo->info->num_philo)
            philo->info->dead = 1;
        pthread_mutex_unlock(&philo->info->write);
        ft_usleep(philo, 1000);
    }
    return (philo);
}

int death_check(t_philo *philo)
{
    if (philo->num_meal < philo->info->num_meal)
    {
        pthread_mutex_lock(&philo->info->death_check);
        if (philo->info->dead == 1)
            return (pthread_mutex_unlock(&philo->info->death_check), 1);
        return (pthread_mutex_unlock(&philo->info->death_check), 0);
    }
    return (1);
}

void *routine(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;

    if (philo->info->num_philo % 2 != 0)
    {
        if (philo->id == philo->info->num_philo && philo->info->num_philo != 1)
            ft_usleep(philo, philo->info->eat_dur * 2);
        if (philo->id % 2 == 0)
            ft_usleep(philo, philo->info->eat_dur);
    }
    else
        ft_usleep(philo, philo->info->eat_dur);
    pthread_mutex_lock(&philo->info->write);
    while (death_check(philo) == 0)
    {
        pthread_mutex_unlock(&philo->info->write);
        eat(philo);
        pthread_mutex_lock(&philo->info->write);
        if (philo->num_meal == philo->info->num_meal)
        {
            pthread_mutex_lock(&philo->info->death_check);
            philo->info->dead = true;
            pthread_mutex_unlock(&philo->info->death_check);
            pthread_mutex_unlock(&philo->info->write);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->info->write);
        messages("is sleeping", philo);
        ft_usleep(philo, philo->info->sleep_dur);
        messages("is thinking", philo);
        pthread_mutex_lock(&philo->info->write);
    }
    pthread_mutex_unlock(&philo->info->write);
    return (philo);
}

void	take_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (philo->info->num_philo % 2 != 0 && philo->info->num_philo != 1)
	  ft_usleep(philo, 50);
    pthread_mutex_lock(left);
	messages("has taken a fork", philo);
	if (left == right)
	{
	   pthread_mutex_unlock(left);
	   ft_usleep(philo, philo->info->til_death);
	   return ;
	}
	pthread_mutex_lock(right);
	messages("has taken a fork", philo);
}

void	eat(t_philo *philo)
{
    if (philo->id % 2 == 0 && philo->info->num_philo != 1)
        take_forks(philo, philo->right_fork, philo->left_fork);
    else
        take_forks(philo, philo->left_fork, philo->right_fork);
    if (philo->info->num_philo == 1)
        return (ft_usleep(philo, philo->info->til_death));
    pthread_mutex_lock(&philo->lock);
	philo->num_meal++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	messages("is eating", philo);
	ft_usleep(philo, philo->info->eat_dur);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
