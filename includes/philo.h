/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:53:13 by scuter            #+#    #+#             */
/*   Updated: 2022/02/25 03:15:31 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				philo_id;
	int				meals;
	int				meals_to_do;
	time_t			time_of_last_meal;
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			limit_of_life;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	struct s_data	*data;
}	t_philo;

typedef struct	s_data
{
	int				nbr_philo;
	int				philo_id;
	time_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				nbr_of_meals;
	pthread_mutex_t	*forks;
	pthread_t		*thread_ids;
	pthread_mutex_t	lock_print;
	t_philo			*all_philos;
}	t_data;

void	invalid_arg(void);
int		str_is_digit(char *str);
int		ft_atoi(const char *str);
long	get_time(void);
void	precise_usleep(int ms);

void	init_data(t_data *data, int argc, char **argv);
void	init_mutex(t_data *data);
void	init_philo(t_data *data);
void	init_threads(t_data *data);

void	end_threads(t_data *data);
void	end_mutex(t_data *data);
void	free_all(t_data *data);

void	*routine(void *ptr);
void	*life_monitor(void *ptr);

void	taking_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif
