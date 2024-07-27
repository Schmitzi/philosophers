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
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
		i++;
	}
	return (0);
}

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	thread[philo->info->count];
	pthread_t	monitor_thread;

	i = 0;
	if (make_threads(philo, thread) == false)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
		return (1);
	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < philo->info->count && philo[i].state != true)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
