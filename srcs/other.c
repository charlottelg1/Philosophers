/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:39:58 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/13 19:34:16 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_philo(t_philo *philo, t_param param)
{
	int	i;

	i = 0;
	while (i < param.nb_philo)
	{
		printf("Philo : %d\nIndex : %d \nAlive : %d\nright_fork : %d\nleft fork : \
		%d\n\n", philo[i].nb_philo, philo[i].index, philo[i].alive, \
		philo[i].right_fork, philo[i].left_fork);
		i++;
	}
}
