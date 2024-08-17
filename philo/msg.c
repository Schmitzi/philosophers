/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:33 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 14:25:52 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	obituary(t_philo *philo)
{
	size_t	time;

	if (philo->info->dead == true)
	{
		time = check_time() - philo->info->begin;
		printf("%zu %zu died\n", time, philo->id);
		return ;
	}
}

void	messages(char *str, t_philo *philo, size_t id)
{
	size_t	time;

	pthread_mutex_lock(&philo->info->death_check);
	if (philo->info->dead != 1)
	{
		time = check_time() - philo->info->begin;
		printf("%zu %zu %s\n", time, id, str);
	}
	pthread_mutex_unlock(&philo->info->death_check);
}
