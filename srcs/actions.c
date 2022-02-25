/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:17:01 by scuter            #+#    #+#             */
/*   Updated: 2022/02/23 19:31:18 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	taking_forks(t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0 && philo->philo_id + 1 != philo->nbr_philo)
	{
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(philo->l_f);
	}
	else
	{
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(philo->r_f);
	}
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", \
			get_time() - philo->start_time, philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", \
		get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->meals += 1;
	philo->time_of_last_meal = get_time();
	precise_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", \
		get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	precise_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", \
		get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}
