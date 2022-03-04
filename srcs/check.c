/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:51:34 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:02:25 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	just_nbr(int ac, char *str)
{
	int	i;

	(void)ac;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != ' '))
		{
			printf("Error: There is a non numeric char in your arguments\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_param(t_param *param)
{
	if (param->nb_philo <= 0)
	{
		printf("Error: There is no Philosopher\n");
		return (0);
	}
	return (1);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number or arguments\n");
		return (0);
	}
	while (i < ac)
	{
		if (!just_nbr(ac, av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_meals_left(t_param *param, t_philo *philos)
{
	int	i;

	i = 0;
	if (param->nb_of_meals == -1)
		return (1);
	while (i < param->nb_philo)
	{
		pthread_mutex_lock(&param->mut_meals);
		if (philos[i].nb_of_meals < param->nb_of_meals)
		{
			pthread_mutex_unlock(&param->mut_meals);
			return (1);
		}
		pthread_mutex_unlock(&param->mut_meals);
		i++;
	}
	return (0);
}
