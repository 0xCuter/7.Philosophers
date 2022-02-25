/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:09:11 by scuter            #+#    #+#             */
/*   Updated: 2022/02/25 03:31:34 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	if (data->nbr_philo < 1)
			invalid_arg();
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nbr_of_meals = -1;
	data->dead = 0;
	if (argc == 6)
	{
		data->nbr_of_meals = ft_atoi(argv[5]);
		if (data->nbr_of_meals < 1)
			invalid_arg();
	}
}

void	init_mutex(t_data *data)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock_print, NULL);
	data->forks = mutex;
}

void	init_philo(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		philos[i].philo_id = i;
		philos[i].nbr_philo = data->nbr_philo;
		philos[i].meals = 0;
		philos[i].meals_to_do = data->nbr_of_meals;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_of_last_meal = get_time();
		philos[i].limit_of_life = data->time_to_die;
		philos[i].stop = 0;
		philos[i].l_f = \
			&data->forks[philos[i].philo_id];
		philos[i].r_f = \
			&data->forks[(philos[i].philo_id + 1) % data->nbr_philo];
		philos[i].data = data;
		i++;
	}
	data->all_philos = philos;
}

void	init_threads(t_data *data)
{
	pthread_t	*threads;
	pthread_t	lm_thread;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_create(&threads[i], NULL, \
			routine, (void *)&data->all_philos[i]);
		i++;
	}
	pthread_create(&lm_thread, NULL, life_monitor, (void *)data->all_philos);
	pthread_join(lm_thread, NULL);
	data->thread_ids = threads;
}
