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
#include <pthread.h>

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
	pthread_t	mon;

	i = 0;

	philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (philo->thread == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (false);
	if (make_threads(philo, mon, philo->thread) == false)
		return (free(philo->thread),false);
	if (pthread_join(mon, NULL) != 0)
		return (free(philo->thread), false);
	while (i < philo->info->count)
	{
		if (pthread_join(philo->thread[i], NULL) != 0)
			return (free(philo->thread), false);
		i++;
	}
	return (true);
}
