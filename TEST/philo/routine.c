#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <complex.h>
#include <pthread.h>
#include <sys/time.h>

void	messages(char *str, t_philo *philo, size_t id)
{
	size_t	time;

	pthread_mutex_lock(&philo->info->death_check);
	if (philo->info->dead != 1)
	{
		time = get_timestamp() - philo->info->begin;
		printf("%zu %zu %s\n", time, id, str);
		pthread_mutex_unlock(&philo->info->death_check);
		return ;
	}
	pthread_mutex_unlock(&philo->info->death_check);
}

static int	check_all_finished(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->count)
	{
		pthread_mutex_lock(&philo->info->death_check);
		pthread_mutex_lock(&philo[i].lock);
		if (philo[i].stop == 1)
			philo->info->end++;
		if (philo->info->end == philo->info->count)
		{
			pthread_mutex_unlock(&philo[i].lock);
			pthread_mutex_unlock(&philo->info->death_check);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
		pthread_mutex_unlock(&philo->info->death_check);
		i++;
	}
	return (0);
}

size_t	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Failed to get time\n", 2);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	ft_dead_msg(t_philo *philo, size_t i)
{
	size_t	time;

	if (philo->info->dead == 1)
	{
		time = get_timestamp() - philo->info->begin;
		printf("%zu %zu died\n", time, i);
		return ;
	}
}

static int	check_any_dead(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->count)
	{
		pthread_mutex_lock(&philo->info->death_check);
		pthread_mutex_lock(&philo[i].lock);
		if ((get_timestamp() - philo[i].last_meal) >= philo->info->til_death)
		{
			philo->info->dead = 1;
			ft_dead_msg(philo, philo[i].id);
			pthread_mutex_unlock(&philo[i].lock);
			pthread_mutex_unlock(&philo->info->death_check);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
		pthread_mutex_unlock(&philo->info->death_check);
		i++;
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_all_finished(philo) == 1 || check_any_dead(philo) == 1)
		{
			return (NULL);
		}
	}
	return (ptr);
}

int death_check(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->death_check);
    if (philo->info->dead == 1)
    {
        pthread_mutex_unlock(&philo->info->death_check);
        return 1;
    }
    pthread_mutex_unlock(&philo->info->death_check);
    return 0;
}


void *routine(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    if (philo->info->count % 2 == 0)
	{
		if (philo->id % 2 != 0)
			ft_usleep (philo, philo->info->eat_dur);
	}
	else if (philo->info->count % 2 != 0)
	{
		if (philo->id == philo->info->count
			&& philo->info->count != 1)
			ft_usleep (philo, (philo->info->eat_dur * 2));
		if (philo->id % 2 == 0)
			ft_usleep (philo, philo->info->eat_dur);
	}
    pthread_mutex_lock(&philo->info->write);
    while (death_check(philo) == 0 && philo->meals_eaten < philo->info->meals)
    {
        pthread_mutex_unlock(&philo->info->write);
        eat(philo);
        pthread_mutex_lock(&philo->info->write);
        if (philo->meals_eaten == philo->info->meals)
        {
            pthread_mutex_lock(&philo->info->death_check);
            philo->stop = 1;
            pthread_mutex_unlock(&philo->info->death_check);
            pthread_mutex_unlock(&philo->info->write);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->info->write);
        messages("is sleeping", philo, philo->id);
        ft_usleep(philo, philo->info->sleep_dur);
        messages("is thinking", philo, philo->id);
        pthread_mutex_lock(&philo->info->write);
    }
    pthread_mutex_unlock(&philo->info->write);
    return (philo);
}

void take_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right)
{
    if (philo->info->count % 2 != 0 && philo->info->count != 1)
        ft_usleep(philo, 50);
    pthread_mutex_lock(left);
    messages("has taken a fork", philo, philo->id);
    if (left == right)
    {
        pthread_mutex_unlock(left);
        ft_usleep(philo, philo->info->til_death);
        return;
    }
    pthread_mutex_lock(right);
    messages("has taken a fork", philo, philo->id);
}

void eat(t_philo *philo)
{
    pthread_mutex_t *left;
    pthread_mutex_t *right;

    if (philo->id % 2 == 0 && philo->info->count != 1)
    {
        left = philo->right_fork;
        right = philo->left_fork;
    }
    else
    {
        left = philo->left_fork;
        right = philo->right_fork;
    }
    take_forks(philo, left, right);
    if (philo->info->count == 1)
    {
        ft_usleep(philo, philo->info->til_death);
        return;
    }
    pthread_mutex_lock(&philo->lock);
    philo->meals_eaten++;
    philo->last_meal = get_timestamp();
    pthread_mutex_unlock(&philo->lock);
    messages("is eating", philo, philo->id);
    ft_usleep(philo, philo->info->eat_dur);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
