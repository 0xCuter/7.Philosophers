/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:52:46 by scuter            #+#    #+#             */
/*   Updated: 2022/02/25 03:04:58 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		invalid_arg();
	argv++;
	while(*argv)
	{
		if (!str_is_digit(*argv) || !ft_atoi(*argv))
			invalid_arg();
		argv++;
	}
}

int	main (int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_data(&data, argc, argv);
	init_mutex(&data);
	init_philo(&data);
	init_threads(&data);
	end_threads(&data);
	end_mutex(&data);
	free_all(&data);
	return (0);
}

