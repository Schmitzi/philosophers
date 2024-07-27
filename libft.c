/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:01:22 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:01:46 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *str, int fd)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
	return (0);
}

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	num;
	long long	sign;

	sign = 1;
	num = 0;
	i = 0;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\v'
		|| *nptr == '\r' || *nptr == '\f')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == 1 && (num > (LLONG_MAX - (nptr[i] - '0')) / 10))
			return (LLONG_MAX);
		else if (sign == -1 && (num > (LLONG_MAX - (nptr[i] - '0')) / 10))
			return (LLONG_MIN);
		num = (nptr[i] - '0') + (10 * num);
		i++;
	}
	return (num * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
