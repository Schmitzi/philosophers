/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:03:03 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 14:32:45 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_end(t_philo *philo)
{
	size_t	i;

	i = -1;
	while (++i < philo->info->count)
	{
		pthread_mutex_lock(&philo->info->death_check);
		pthread_mutex_lock(&philo[i].lock);
		if ((check_time() - philo[i].last_meal) >= philo->info->til_death)
		{
			philo->info->dead = true;
			obituary(philo);
			pthread_mutex_unlock(&philo[i].lock);
			pthread_mutex_unlock(&philo->info->death_check);
			return (true);
		}
		if (philo[i].stop == true && ++philo->info->end == philo->info->count)
		{
			pthread_mutex_unlock(&philo[i].lock);
			pthread_mutex_unlock(&philo->info->death_check);
			return (true);
		}
		pthread_mutex_unlock(&philo[i].lock);
		pthread_mutex_unlock(&philo->info->death_check);
	}
	return (false);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (dead_end(philo) == 1)
			return (NULL);
		usleep(200);
	}
	return (ptr);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	form_queue(philo);
	pthread_mutex_lock(&philo->info->write);
	while (death_check(philo) == false)
	{
		pthread_mutex_unlock(&philo->info->write);
		eat(philo);
		pthread_mutex_lock(&philo->info->write);
		if (meal_check(philo) == false)
			return (NULL);
		pthread_mutex_unlock(&philo->info->write);
		messages("is sleeping", philo, philo->id);
		ft_usleep(philo, philo->info->sleep_dur);
		messages("is thinking", philo, philo->id);
		pthread_mutex_lock(&philo->info->write);
	}
	pthread_mutex_unlock(&philo->info->write);
	return (philo);
}

void	take_forks(t_philo *philo, pthread_mutex_t *left, \
	pthread_mutex_t *right)
{
	if (philo->info->count % 2 != 0 && philo->info->count != 1)
		ft_usleep(philo, philo->info->eat_dur);
	pthread_mutex_lock(left);
	messages("has taken a fork", philo, philo->id);
	if (left == right)
	{
		pthread_mutex_unlock(left);
		ft_usleep(philo, philo->info->til_death);
		return ;
	}
	pthread_mutex_lock(right);
	messages("has taken a fork", philo, philo->id);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->info->count != 1)
		take_forks(philo, philo->right_fork, philo->left_fork);
	else
		take_forks(philo, philo->left_fork, philo->right_fork);
	if (philo->info->count == 1)
		return (ft_usleep(philo, philo->info->til_death));
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = check_time();
	pthread_mutex_unlock(&philo->lock);
	messages("is eating", philo, philo->id);
	ft_usleep(philo, philo->info->eat_dur);
	pthread_mutex_lock(&philo->lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
