/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:47 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:02:48 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_philo *philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&philo->info->write, NULL);
	pthread_mutex_init(&philo->info->death_check, NULL);
	while (i < philo->info->count)
	{
		pthread_mutex_init(&philo->info->forks[i], NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
	return (true);
}

void	destroy_mutex(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->count && philo[i].state == 2)
	{
		pthread_mutex_destroy(&philo->info->forks[i]);
		pthread_mutex_destroy(&philo[i].lock);
		i++;
	}
	pthread_mutex_destroy(&philo->info->write);
	pthread_mutex_destroy(&philo->info->death_check);
}
