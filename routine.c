/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:31:05 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:13:31 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	philo->until_death = philo->info->death_time + get_time();
	if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo) == 1)
	{
		free(philo);
		return ((void *)1);
	}
	while (philo->info->dead == 0)
	{
		eat(philo);
		if (philo->info->dead == 0)
		{
			messages("is thinking", philo);
			ft_usleep(1000);
		}
	}
	if (pthread_join(philo->thread, NULL) == 1)
		return (free(philo), (void *)1);
	//free(philo);
	return (ptr);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	while (philo->info->dead == 0)
	{
		pthread_mutex_lock(&philo->info->write);
		if (philo->info->finished >= philo->info->num)
			philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->write);
		ft_usleep(1000);
	}
	return (ptr);
}
