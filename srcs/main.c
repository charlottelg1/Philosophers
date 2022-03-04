/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:36 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:00:15 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_msg(t_philo *philo, char *str)
{
	int	time;

	time = ft_time() - philo->param->start;
	pthread_mutex_lock(&philo->param->mut_msg);
	printf("%d Philo %d %s\n", time, philo->index, str);
	pthread_mutex_unlock(&philo->param->mut_msg);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		ft_sleep(1, philo->param);
	while ((all_alive(philo->param)) && ((philo->nb_of_meals < \
	philo->param->nb_of_meals) || (philo->param->nb_of_meals == -1)))
	{
		if (!all_alive(philo->param))
			break ;
		take_fork(philo);
		if (philo->param->nb_philo == 1)
		{
			ft_sleep(philo->param->time_to_die, philo->param);
			return (NULL);
		}
		start_eating(philo);
		let_fork(philo);
		start_sleeping(philo);
		start_thinking(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_param		param;
	t_philo		*philos;
	int			i;

	i = 0;
	philos = NULL;
	if (!check_arg(ac, av))
		return (0);
	if (!init_param(ac, av, &param))
		return (0);
	philos = init_philo(&param);
	if (philos == 0)
	{
		free_all(&param, philos);
		return (0);
	}
	param.philos = philos;
	if (!lets_thread(&param, philos))
	{
		free_all(&param, philos);
		return (0);
	}
	free_all(&param, philos);
	return (0);
}
