/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:35:12 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:02:02 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	creating_threads(t_param *param, t_philo *philos)
{
	int	i;
	int	create;

	i = 0;
	while (i < param->nb_philo)
	{
		create = pthread_create(&philos[i].thread, NULL, (void *) routine, \
		(void *)&philos[i]);
		if (create != 0)
		{
			printf("Creating philo nb %d failed.\n", i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	joining_threads(t_param *param, t_philo *philos)
{
	int	i;
	int	create;

	i = 0;
	while (i < param->nb_philo)
	{
		create = pthread_join(philos[i].thread, NULL);
		if (create != 0)
		{
			printf("Joining philo nb %d failed.\n", i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	lets_thread(t_param *param, t_philo *philos)
{
	if (!creating_threads(param, philos))
		return (0);
	while (param->alive && check_meals_left(param, philos))
		check_death(param, philos);
	if (!joining_threads(param, philos))
		return (0);
	return (1);
}
