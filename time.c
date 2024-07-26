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
#include <pthread.h>
#include <sys/types.h>

void	ft_usleep(t_philo *philo, unsigned int ms)
{
	u_int64_t	begin;
	u_int64_t	curr;
	size_t		elapsed;

	begin = check_time();
	while (check_time())
	{
		curr = check_time();
		elapsed = curr - begin;
		pthread_mutex_lock(&philo->info->death_check);
		if (elapsed >= ms || philo->info->dead != 0)
		{
			pthread_mutex_unlock(&philo->info->death_check);
	 		break ;
		}
		pthread_mutex_unlock(&philo->info->death_check);
		usleep(100);
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
