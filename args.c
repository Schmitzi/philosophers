/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:59:46 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:00:12 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checker(char **argv)
{
	int			i;
	int			j;
	long long	num;

	i = 1;
	j = 0;
	while (argv[i])
	{
		num = ft_atoll(argv[i]);
		if (num > INT_MAX || num < 0)
			return (ft_perror("Out of range"), 1);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_perror("Out of range"), 1);
			j++;
		}
		i++;
	}
	return (0);
}
