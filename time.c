/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:06:12 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:13:54 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_perror("Time Failed\n");
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, unsigned int ms)
{
	struct timeval	begin;
	struct timeval	curr;
	size_t			elapsed;

	gettimeofday(&begin, NULL);
	while (1)
	{
		gettimeofday(&curr, NULL);
		elapsed = (curr.tv_sec - begin.tv_sec) * 1000 + \
			(curr.tv_usec - begin.tv_usec) / 1000;
		pthread_mutex_lock(&philo->info->death_check);
		if (elapsed >= ms || philo->info->dead != 0)
		{
			pthread_mutex_unlock(&philo->info->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->info->death_check);
		usleep(400);
	}
	return ;
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
