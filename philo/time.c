/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:06:12 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 12:31:23 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, unsigned int ms)
{
	u_int64_t	start_time;
	u_int64_t	current_time;
	size_t		time_elapsed;

	start_time = check_time();
	while (1)
	{
		current_time = check_time();
		time_elapsed = current_time - start_time;
		pthread_mutex_lock(&philo->info->death_check);
		if (time_elapsed >= ms || philo->info->dead != 0)
		{
			pthread_mutex_unlock(&philo->info->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->info->death_check);
		if (ms > time_elapsed)
			usleep(ms - time_elapsed);
		else
			usleep(10);
	}
}

size_t	check_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Time check failed\n", 2);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
