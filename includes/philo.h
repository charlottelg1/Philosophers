/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:25:07 by cle-gran          #+#    #+#             */
/*   Updated: 2022/02/25 20:01:42 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_param
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				alive;
	long			start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mut_msg;
	pthread_mutex_t	mut_death;
	pthread_mutex_t	mut_check;
	pthread_mutex_t	mut_meals;
	pthread_mutex_t	mut_other;
	struct s_philo	*philos;
}	t_param;

typedef struct s_philo
{
	int			nb_philo;
	int			index;
	int			alive;
	int			left_fork;
	int			right_fork;
	int			nb_of_meals;
	long		last_meal;
	pthread_t	thread;
	t_param		*param;
}	t_philo;

/* MAIN */
int		main(int ac, char **av);
void	*routine(void *arg);
void	display_msg(t_philo *philo, char *str);

/*CHECK & INIT*/
int		init_param(int ac, char **av, t_param *param);
int		check_arg(int ac, char **av);
int		check_param(t_param *param);
int		just_nbr(int ac, char *str);
t_philo	*init_philo(t_param *param);
int		lets_thread(t_param *param, t_philo *philos);
int		check_meals_left(t_param *param, t_philo *philos);

/*ACTION*/
int		take_fork(t_philo *philo);
void	start_eating(t_philo *philo);
void	let_fork(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	start_thinking(t_philo *philo);

/*DEATH*/
void	free_all(t_param *param, t_philo *philos);
int		all_alive(t_param *param);
void	check_death(t_param *param, t_philo *philos);

/*UTILS*/
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str);
void	ft_putnbr(int nb, int *count);
int		ft_atoi(char *str);
void	error_atoi(void);
int		checkoverflow(char *str);
void	ft_sleep(int ms, t_param *param);
long	ft_time(void);

/*OTHER*/
void	display_philo(t_philo *philo, t_param param);

#endif
