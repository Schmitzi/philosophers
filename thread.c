/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:05:02 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 16:23:30 by mgeiger-         ###   ########.fr       */
/*   Updated: 2024/07/31 16:17:38 by mgeiger-         ###   ########.fr       */
/*   Updated: 2024/08/01 19:41:56 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_philo *philo, pthread_t mon, pthread_t *thread)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < philo->info->count)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
			if (pthread_join(mon, NULL) != 0)
				return (false);
			while (j < i)
			{
				if (pthread_join(thread[j], NULL) != 0)
					return (false);
				j++;
			}
			pthread_mutex_unlock(&philo[i].lock);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].lock);
		i++;
	}
	return (true);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	*thread;
	pthread_t	mon;

	i = 0;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (thread == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (free(thread), false);
	if (make_threads(philo, mon, thread) == false)
		return (free(thread), false);
	if (pthread_join(mon, NULL) != 0)
		return (free(thread), false);
	while (i < philo->info->count)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free(thread), false);
		i++;
	}
	return (free(thread), true);
}
/*
int	make_threads(t_philo *philo, pthread_t mon, pthread_t *thread)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
>>>>>>> 7e4668457dfb995ee09aeea4bed8bc9c31e29b89
	while (i < philo->info->count)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
<<<<<<< HEAD
			pthread_join(mon, NULL);
			while (j < i)
			{
				pthread_join(thread[j], NULL);
				j++;
			}
			pthread_mutex_unlock(&philo[i].lock);
			free(thread);
=======
			if (pthread_join(mon, NULL) != 0)
				return (free(thread), false);
			while (j < i)
			{
				if (pthread_join(thread[j], NULL) != 0)
					return (free(thread), false);
				j++;
			}
			pthread_mutex_unlock(&philo[i].lock);
>>>>>>> 7e4668457dfb995ee09aeea4bed8bc9c31e29b89
			return (false);
		}
		pthread_mutex_unlock(&philo[i].lock);
		i++;
	}
	return (true);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	*thread;
	pthread_t	mon;

	i = 0;
<<<<<<< HEAD

=======
>>>>>>> 7e4668457dfb995ee09aeea4bed8bc9c31e29b89
	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (thread == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (free(thread), false);
	if (make_threads(philo, mon, thread) == false)
<<<<<<< HEAD
		return (false);
	if (pthread_join(mon, NULL) != 0)
		return (free(thread),false);
=======
		return (free(thread), false);
	if (pthread_join(mon, NULL) != 0)
		return (free(thread), false);
>>>>>>> 7e4668457dfb995ee09aeea4bed8bc9c31e29b89
	while (i < philo->info->count)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free(thread), false);
		i++;
	}
<<<<<<< HEAD
	free(thread);
	return (true);
}
/*
int	make_threads(t_philo *philo, pthread_t mon, pthread_t *thread)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < philo->info->count)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
			if (pthread_join(mon, NULL) != 0)
				return (free(thread), false);
			while (j < i)
			{
				if (pthread_join(thread[j], NULL) != 0)
					return (free(thread), false);
				j++;
			}
			pthread_mutex_unlock(&philo[i].lock);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].lock);
		i++;
	}
	return (true);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	*thread;
	pthread_t	mon;

	i = 0;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (thread == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (free(thread), false);
	if (make_threads(philo, mon, thread) == false)
		return (free(thread), false);
	if (pthread_join(mon, NULL) != 0)
		return (free(thread), false);
	while (i < philo->info->count)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free(thread), false);
		i++;
	}
=======
>>>>>>> 7e4668457dfb995ee09aeea4bed8bc9c31e29b89
	return (free(thread), true);
}*/
