/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:02:28 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (arg_checker(argc, argv))
			return (false);
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (philo == NULL)
			return (ft_perror("Philo malloc failed"), false);
		if (init_all(philo, argv) == false)
			return (ft_exit(philo), false);
		if (thread_init(philo) == 0)
			return (ft_exit(philo), false);
		return (ft_exit(philo), true);
	}
	else
		ft_perror("Error: Invalid number of arguments\n");
	return (true);
}
