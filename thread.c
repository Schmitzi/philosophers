/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:05:02 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/05 16:07:39 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_philo *philo, pthread_t mon, pthread_t *thread)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (++i < philo->info->count)
	{
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
			if (pthread_join(mon, NULL) != 0)
				return (pthread_mutex_unlock(&philo[i].lock), false);
			while (j < i)
			{
				if (pthread_join(thread[j], NULL) != 0)
					return (pthread_mutex_unlock(&philo[i].lock), false);
				j++;
			}
			return (pthread_mutex_unlock(&philo[i].lock), false);
		}
		pthread_mutex_unlock(&philo[i].lock);
	}
	return (true);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	mon;

	i = 0;
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (philo->thread == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (false);
	if (make_threads(philo, mon, philo->thread) == false)
		return (false);
	if (pthread_join(mon, NULL) != 0)
		return (false);
	while (i < philo->info->count)
	{
		if (pthread_join(philo->thread[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}
