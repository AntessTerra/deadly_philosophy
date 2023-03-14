/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/14 15:57:18 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		base;

	i = 0;
	sign = 1;
	base = 0;
	if (nptr[i] == '\0')
		return (0);
	while (nptr[i] <= ' ' && nptr[i] != '\e')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		base = 10 * base + (nptr[i++] - '0');
	if ((nptr[i] < '0' || nptr[i] > '9') && nptr[i] != '\0')
		return (-1);
	return (base * sign);
}

void	init_others(t_philo **philos)
{
	int	i;

	i = 0;
	while (++i < philos[0]->n_phil)
	{
		(*philos)->n_phil = philos[0]->n_phil;
		(*philos)->die = philos[0]->die;
		(*philos)->eat = philos[0]->eat;
		(*philos)->sleep = philos[0]->sleep;
		(*philos)->to_eat = philos[0]->to_eat;
	}
}

void	init_philo(int argc, char **argv, t_philo **philos)
{
	if (argc < 5 || argc > 6)
		return (free(*philos), exit(1));
	(*philos)->n_phil = ft_atoi(argv[1]);
	(*philos)->die = ft_atoi(argv[2]);
	(*philos)->eat = ft_atoi(argv[3]);
	(*philos)->sleep = ft_atoi(argv[4]);
	if ((*philos)->n_phil < 1 || (*philos)->die < 0 || (*philos)->eat < 0
		|| (*philos)->sleep < 0)
		return (free(*philos), exit(2));
	if (argc == 6)
	{
		(*philos)->to_eat = ft_atoi(argv[5]);
		if ((*philos)->to_eat < 0)
			return (free(*philos), exit(2));
	}
	else
		(*philos)->to_eat = -1;
	init_others(philos);
}

void	*thread_routine(void *data)
{
	int	*i;

	i = (int *) data;
	printf("HELLO from %d\n", *i);
	pthread_exit (NULL);
}

int	main(int argc, char **argv)
{
	int			n;
	t_philo		*philos;

	philos = malloc(5 * sizeof(t_philo));
	init_philo(argc, argv, &philos);
	n = -1;
	while (++n < 5)
	{
		philos->id = n;
		pthread_mutex_init(&philos[n].mutex, NULL);
		pthread_create(&philos[n].thread, NULL, thread_routine, &n);
	}
	n = -1;
	while (++n < 5)
		pthread_join(philos[n].thread, NULL);
	n = -1;
	while (++n < 5)
		pthread_mutex_destroy(&philos[n].mutex);
	free(philos);
	return (0);
}
