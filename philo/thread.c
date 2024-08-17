/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:05:02 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/17 12:15:24 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_init(t_philo *philo)
{
	size_t		i;
	pthread_t	mon;
	pthread_t	*threads;

	i = -1;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->info->count);
	if (threads == NULL)
		return (false);
	if (pthread_create(&mon, NULL, monitor, philo) != 0)
		return (stop_threads(threads, i), false);
	while (++i < philo->info->count && &philo[i])
		if (pthread_create(&threads[i], NULL, routine, &philo[i]) != 0)
			return (stop_threads(threads, i), false);
	if (pthread_join(mon, NULL) != 0)
		return (stop_threads(threads, i), false);
	i = -1;
	while (++i < philo->info->count)
		if (pthread_join(threads[i], NULL) != 0)
			return (stop_threads(threads, i), false);
	return (free(threads), true);
}
