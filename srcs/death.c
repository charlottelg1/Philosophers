/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:24:44 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/20 19:53:16 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_alive(t_param *param)
{
	pthread_mutex_lock(&param->mut_check);
	if (param->alive == 0)
	{
		pthread_mutex_unlock(&param->mut_check);
		return (0);
	}
	pthread_mutex_unlock(&param->mut_check);
	return (1);
}

int	time_passed(t_philo philo, long now, t_param *param)
{
	long	last_meal_value;

	last_meal_value = 0;
	pthread_mutex_lock(&param->mut_check);
	last_meal_value = philo.last_meal;
	pthread_mutex_unlock(&param->mut_check);
	return (now - last_meal_value);
}

void	check_death(t_param *param, t_philo *philos)
{
	int		i;
	long	now;

	i = 0;
	pthread_mutex_lock(&param->mut_death);
	while (all_alive(param) && check_meals_left(param, philos))
	{
		now = ft_time();
		if (time_passed(philos[i], now, param) > param->time_to_die)
		{
			display_msg(&philos[i], DEAD);
			param->alive = 0;
		}
		i++;
		if (i == param->nb_philo)
			i = 0;
	}
	pthread_mutex_unlock(&param->mut_death);
}

void	free_all(t_param *param, t_philo *philos)
{
	int	i;

	i = 0;
	if (param->fork)
	{
		while (i < param->nb_philo)
		{
			pthread_mutex_destroy(&param->fork[i]);
			i++;
		}
		free(param->fork);
	}
	pthread_mutex_destroy(&param->mut_msg);
	pthread_mutex_destroy(&param->mut_death);
	pthread_mutex_destroy(&param->mut_check);
	pthread_mutex_destroy(&param->mut_meals);
	if (philos)
		free(philos);
}
