/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:31:09 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:53:06 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	thread;

	i = -1;
	thread = 0;
	while (++i < philo->info->num)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread, NULL, &routine, &philo[i]) != 0)
		{
			philo[i].state = 2;
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
	}
	if (pthread_create(&thread, NULL, &monitor, philo) != 0)
		return (1);
	i = -1;
	pthread_join(thread, NULL);
	while (i < philo->info->num && philo[i].state != 2)
		if (pthread_join(thread, NULL) != 0)
			return (1);
	return (0);
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
	ft_usleep(philo->info->sleep_time * 1000);
}

void	eat(t_philo *philo)
{
	int64_t	time;

	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eat = 1;
	time = get_time();
	philo->until_death = time + philo->info->death_time;
	messages("is eating", philo);
	ft_usleep(philo->info->eat_time * 1000);
	philo->meals++;
	philo->eat = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
	messages("is thinking", philo);
	ft_usleep(1000);
}

void	ft_usleep(unsigned int ms)
{
	struct timeval	start;
	struct timeval	current;
	unsigned int	elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < ms)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000 + \
		(current.tv_usec - start.tv_usec);
	}
}
