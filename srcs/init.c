/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:51:54 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:02:35 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(t_param *param)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * param->nb_philo);
	if (!philos)
	{
		printf("Error: The malloc failed to create philos\n");
		return (0);
	}
	while (i < param->nb_philo)
	{
		philos[i].nb_philo = param->nb_philo;
		philos[i].index = i + 1;
		philos[i].alive = 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % param->nb_philo;
		philos[i].nb_of_meals = 0;
		philos[i].param = param;
		philos[i].last_meal = ft_time();
		i++;
	}
	return (philos);
}

int	init_mutex(t_param *param)
{
	int	i;

	i = 0;
	param->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	param->nb_philo);
	if (!param->fork)
	{
		printf("Error : The malloc of the forks failed\n");
		return (0);
	}
	while (i < param->nb_philo)
	{
		pthread_mutex_init(&param->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&param->mut_msg, NULL);
	pthread_mutex_init(&param->mut_death, NULL);
	pthread_mutex_init(&param->mut_check, NULL);
	pthread_mutex_init(&param->mut_meals, NULL);
	return (1);
}

int	init_param(int ac, char **av, t_param *param)
{
	int	i;

	i = 0;
	param->nb_philo = ft_atoi(av[1]);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (param->nb_philo < 0 || param->time_to_die < 0 || param->time_to_eat < 0 \
	|| param->time_to_sleep < 0)
		return (0);
	param->alive = 1;
	param->start = ft_time();
	if (ac == 6)
		param->nb_of_meals = ft_atoi(av[5]);
	else
		param->nb_of_meals = -1;
	if (param->nb_of_meals == -2)
		return (0);
	if (!check_param(param))
		return (0);
	if (!init_mutex(param))
		return (0);
	return (1);
}
