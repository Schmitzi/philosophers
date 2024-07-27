/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:05:02 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:05:22 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	make_threads(t_philo *philo, pthread_t *thread)
{
	size_t	i;

	i = 0;
	while (i < philo->info->count)
	{
		philo[i].info = philo->info;
		pthread_mutex_lock(&philo[i].lock);
		if (pthread_create(&thread[i], NULL, routine, &philo[i]) != 0)
		{
			philo[i].state = true;
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
	pthread_t	monitor_thread;

	i = 0;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (thread == NULL)
		return (false);
	if (make_threads(philo, thread) == false)
		return (free(thread), false);
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
		return (false);
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		return (false);
	while (i < philo->info->count && philo[i].state != true)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (false);
		i++;
	}
	return (false);
}
