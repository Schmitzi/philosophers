/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:07:12 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 14:27:17 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	if (philo->meals_eaten < philo->info->meals)
	{
		pthread_mutex_lock(&philo->info->death_check);
		if (philo->info->dead == true)
			return (pthread_mutex_unlock(&philo->info->death_check), true);
		return (pthread_mutex_unlock(&philo->info->death_check), false);
	}
	return (true);
}

void	form_queue(t_philo *philo)
{
	if (philo->info->count % 2 != 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo, philo->info->eat_dur);
	}
	else
	{
		if (philo->id % 2 != 0)
			ft_usleep(philo, philo->info->eat_dur);
	}
}

int	meal_check(t_philo *philo)
{
	if (philo->meals_eaten == philo->info->meals)
	{
		pthread_mutex_lock(&philo->info->death_check);
		philo->stop = true;
		pthread_mutex_unlock(&philo->info->death_check);
		pthread_mutex_unlock(&philo->info->write);
		return (false);
	}
	return (true);
}
