/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 21:38:20 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/28 19:32:35 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putchar(char c, int *count)
{
	(void)count;
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str, 0);
		str++;
	}
}

void	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
	{
		ft_putchar('-', count);
		ft_putchar('2', count);
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb *= (-1);
	}
	if (nb / 10 != 0)
		ft_putnbr(nb / 10, count);
	ft_putchar((nb % 10) + '0', count);
}

void	ft_sleep(int ms, t_param *param)
{
	int	i;
	int	life;

	i = 100;
	pthread_mutex_lock(&param->mut_check);
	life = param->alive;
	pthread_mutex_unlock(&param->mut_check);
	while (i <= ms && life)
	{
		pthread_mutex_lock(&param->mut_check);
		life = param->alive;
		pthread_mutex_unlock(&param->mut_check);
		usleep(100 * 1000);
		i += 100;
	}
	pthread_mutex_lock(&param->mut_check);
	if (life)
	{
		pthread_mutex_unlock(&param->mut_check);
		usleep((ms % 100) * 1000);
	}
	else
		pthread_mutex_unlock(&param->mut_check);
}

long	ft_time(void)
{
	struct timeval	now;
	long			timestamp;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (timestamp);
}
