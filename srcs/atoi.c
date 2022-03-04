/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:49:33 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:02:06 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	checkoverflow(char *str)
{
	int	i;

	i = 0;
	while (*str >= '0' && *str <= '9')
	{
		i++;
		str++;
	}
	if (i > 11)
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	long	res;
	int		sign;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (str[i])
		res = res * 10 + (str[i++] - 48);
	if (res * sign >= 2147483648 || res * sign < -2147483648 || \
	!checkoverflow(str))
	{
		printf("One of the argument is not a valid int\n");
		return (-2);
	}
	return (res * sign);
}
