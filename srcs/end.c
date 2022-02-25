/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 02:18:40 by scuter            #+#    #+#             */
/*   Updated: 2022/02/25 03:15:31 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_threads(t_data *data)
{
	int	i;

	if (data->nbr_philo == 1)
	{
		pthread_mutex_unlock(&data->forks[0]);
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->thread_ids[i], NULL);
		i++;
	}
}

void	end_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_unlock(&(*data).lock_print);
	pthread_mutex_destroy(&(*data).lock_print);
}

void	free_all(t_data *data)
{
	free(data->thread_ids);
	free(data->all_philos);
	free(data->forks);
}
