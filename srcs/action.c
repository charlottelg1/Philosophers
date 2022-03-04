/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:56:29 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/28 19:32:01 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_thinking(t_philo *philo)
{
	if (philo->param->time_to_eat >= philo->param->time_to_sleep)
	{
		if (all_alive(philo->param) && philo->nb_of_meals != \
		philo->param->nb_of_meals)
			display_msg(philo, THINK);
		ft_sleep((philo->param->time_to_die - philo->param->time_to_eat - \
		philo->param->time_to_sleep) / 2, philo->param);
	}
}

void	start_sleeping(t_philo *philo)
{
	if (all_alive(philo->param) && check_meals_left(philo->param, \
	philo->param->philos))
		display_msg(philo, SLEEP);
	ft_sleep(philo->param->time_to_sleep, philo->param);
}

void	let_fork(t_philo *philo)
{
	if (philo->param->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->param->fork[philo->right_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->param->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->param->fork[philo->left_fork]);
}

void	start_eating(t_philo *philo)
{
	if (all_alive(philo->param))
		display_msg(philo, EAT);
	pthread_mutex_lock(&philo->param->mut_meals);
	philo->last_meal = ft_time();
	philo->nb_of_meals += 1;
	pthread_mutex_unlock(&philo->param->mut_meals);
	ft_sleep(philo->param->time_to_eat, philo->param);
}

int	take_fork(t_philo *philo)
{
	if (philo->index % 2 != 0)
		pthread_mutex_lock(&philo->param->fork[philo->right_fork]);
	else
		pthread_mutex_lock(&philo->param->fork[philo->left_fork]);
	if (all_alive(philo->param))
		display_msg(philo, FORK);
	if (philo->param->nb_philo == 1)
		return (1);
	if (philo->index % 2 != 0)
		pthread_mutex_lock(&philo->param->fork[philo->left_fork]);
	else
		pthread_mutex_lock(&philo->param->fork[philo->right_fork]);
	if (all_alive(philo->param))
		display_msg(philo, FORK);
	return (1);
}
