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

int	arg_checker(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (*argv[i] == ' ')
		{
			i++;
			continue ;
		}
		if (*argv[i] < '0' || *argv[i] > '9')
			return (ft_perror("Out of range"), 1);
		i++;
	}
	argv++;
	return (0);
}
