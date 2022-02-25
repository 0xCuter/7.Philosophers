/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:43:26 by scuter            #+#    #+#             */
/*   Updated: 2022/02/25 13:37:43 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	meal_count(t_philo *philo)
{
	int	enough;
	int	i;

	if (philo->meals != -1 && philo->meals_to_do > 0)
	{
		enough = 1;
		i = 0;
		while (i < philo->nbr_philo)
		{
			if (philo[i].meals < philo->meals_to_do)
				enough = 0;
			i++;
		}
		if (enough)
		{
			i = 0;
			while (i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->time_of_last_meal = get_time();
	philo->start_time = philo->time_of_last_meal;
	if (philo->philo_id % 2 == 0)
		usleep(philo->time_to_eat * 1000 / 2);
	while (!philo->data->dead)
	{
		if (philo->data->dead || philo->stop || meal_count(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->data->dead || philo->stop || meal_count(philo))
			return (NULL);
		eating(philo);
		if (philo->data->dead || philo->stop || meal_count(philo))
			return (NULL);
		sleeping(philo);
		if (philo->data->dead || philo->stop || meal_count(philo))
			return (NULL);
		thinking(philo);
		if (philo->data->dead || philo->stop || meal_count(philo))
			return (NULL);
	}
	return (NULL);
}

static void	dead_philo(t_philo *philo, int i)
{
	philo->data->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", get_time() - philo->start_time,
		philo[i].philo_id + 1);
	i = 0;
	while (i < philo[i].nbr_philo)
	{
		philo[i].stop = 1;
		i++;
	}
}

void	*life_monitor(void *ptr)
{
	t_philo	*philo;
	long	time;
	int		i;

	philo = (t_philo *)ptr;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = 0;
		while (i < philo->nbr_philo)
		{
			time = get_time();
			if (time - philo[i].time_of_last_meal > philo[i].limit_of_life)
			{
				dead_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
			i++;
		}
		if (meal_count(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
