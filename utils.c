/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:31:12 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:29:11 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(char **argv)
{
	int		i;
	int		j;
	char	c;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			c = argv[i][j];
			if (c == ' ')
			{
				++j;
				continue ;
			}
			if (c < '0' || c > '9')
				return (ft_error("Out of range", NULL), 1);
			++j;
		}
		++i;
	}
	return (0);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_error("Time Failed\n", NULL);
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->info->write);
	time = get_time() - philo->info->start_time;
	if (ft_strcmp("has died", str) == 0 && philo->info->dead == 0)
	{
		printf("%lu %ld %s\n", time, philo->id, str);
		philo->info->dead = 1;
	}
	if (!philo->info->dead)
		printf("%lu %ld %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write);
}
