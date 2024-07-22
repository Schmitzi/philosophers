/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:07:12 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:07:13 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	if (philo->meals_eaten < philo->info->meals)
	{
		pthread_mutex_lock(&philo->info->death_check);
		if (philo->info->dead == 1)
			return (pthread_mutex_unlock(&philo->info->death_check), 1);
		return (pthread_mutex_unlock(&philo->info->death_check), 0);
	}
	return (1);
}

void	form_queue(t_philo *philo)
{
	if (philo->info->count % 2 != 0)
	{
		if (philo->id == philo->info->count && philo->info->count != 1)
			ft_usleep (philo->info->eat_dur * 2);
		if (philo->id % 2 == 0)
			ft_usleep (philo->info->eat_dur);
	}
	else
		if (philo->id % 2 != 0)
			ft_usleep (philo->info->eat_dur);
}

int	meal_check(t_philo *philo)
{
	if (philo->meals_eaten == philo->info->meals)
	{
		pthread_mutex_lock(&philo->info->death_check);
		philo->stop = 1;
		pthread_mutex_unlock(&philo->info->death_check);
		pthread_mutex_unlock(&philo->info->write);
		return (false);
	}
	return (true);
}
