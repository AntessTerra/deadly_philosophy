/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/15 16:34:07 by jbartosi         ###   ########.fr       */
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
		(*philos)[i].n_phil = philos[0]->n_phil;
		(*philos)[i].die = philos[0]->die;
		(*philos)[i].eat = philos[0]->eat;
		(*philos)[i].sleep = philos[0]->sleep;
		(*philos)[i].to_eat = philos[0]->to_eat;
		gettimeofday(&(*philos)[i].created_at, NULL);
	}
}

void	init_philo(int argc, char **argv, t_philo **philos)
{
	if (argc < 5 || argc > 6)
		return (printf("ERROR: Incorect number of arguments\n"), exit(1));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (printf("ERROR: Invalid argument\n"), exit(2));
	*philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	(*philos)->n_phil = ft_atoi(argv[1]);
	(*philos)->die = ft_atoi(argv[2]);
	(*philos)->eat = ft_atoi(argv[3]);
	(*philos)->sleep = ft_atoi(argv[4]);
	gettimeofday(&(*philos)->created_at, NULL);
	if (argc == 6)
	{
		(*philos)->to_eat = ft_atoi(argv[5]);
		if ((*philos)->to_eat < 0)
			return (free(*philos), printf("ERROR: Invalid argument\n"), exit(2));
	}
	else
		(*philos)->to_eat = -1;
	init_others(philos);
}

void	*thread_routine(void *data)
{
	struct s_philo	*philo;
	struct timeval	timenow;

	philo = (struct s_philo *) data;
	gettimeofday(&timenow, NULL);
	printf("%lld %d is eating\n", timesince(philo->created_at, timenow), philo->id);
	milisleep(philo->eat);
	gettimeofday(&timenow, NULL);
	printf("%lld %d is sleeping\n", timesince(philo->created_at, timenow), philo->id);
	milisleep(philo->sleep);
	gettimeofday(&timenow, NULL);
	printf("%lld %d is thinking\n", timesince(philo->created_at, timenow), philo->id);
	pthread_exit (NULL);
}

int	main(int argc, char **argv)
{
	int			n;
	t_philo		*philos;

	init_philo(argc, argv, &philos);
	n = -1;
	while (++n < philos[0].n_phil)
	{
		philos[n].id = n + 1;
		pthread_mutex_init(&philos[n].mutex, NULL);
		pthread_create(&philos[n].thread, NULL, thread_routine, &philos[n]);
	}
	n = -1;
	while (++n < philos[0].n_phil)
		pthread_join(philos[n].thread, NULL);
	n = -1;
	while (++n < philos[0].n_phil)
		pthread_mutex_destroy(&philos[n].mutex);
	return (free(philos), 0);
}
