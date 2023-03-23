/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:46:22 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/19 16:50:42 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timesince(struct timeval then, struct timeval now)
{
	long long	start;
	long long	end;

	start = (then.tv_sec * 1000) + (then.tv_usec / 1000);
	end = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (end - start);
}

void	milisleep(int microsec)
{
	usleep(microsec * 1000);
}

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

void	init_others(t_philo **philos, int **forks, pthread_mutex_t	**mutexes)
{
	int	i;

	i = 0;
	(*forks)[0] = 1;
	(*philos)[0].n_ate = 0;
	(*philos)[0].alive = 1;
	(*philos)[0].init_sleep = 1;
	while (++i < philos[0]->n_phil)
	{
		(*philos)[i].n_phil = philos[0]->n_phil;
		(*philos)[i].die = philos[0]->die;
		(*philos)[i].eat = philos[0]->eat;
		(*philos)[i].sleep = philos[0]->sleep;
		(*philos)[i].to_eat = philos[0]->to_eat;
		(*philos)[i].alive = 1;
		(*philos)[i].init_sleep = 1;
		(*philos)->n_ate = 0;
		(*forks)[i] = 1;
		(*philos)[i].forks = *forks;
		(*philos)[i].mutexes = *mutexes;
		gettimeofday(&(*philos)[i].created_at, NULL);
	}
}

void	init_philo(int argc, char **argv, t_philo **philos, int **forks)
{
	pthread_mutex_t	*mutexes;

	if (argc < 5 || argc > 6)
		return (printf("ERROR: Incorect number of arguments\n"), exit(1));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (printf("ERROR: Invalid argument\n"), exit(2));
	*philos = malloc((ft_atoi(argv[1]) * sizeof(t_philo))
			+ ft_atoi(argv[1]) * sizeof(int) + ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	*forks = malloc(ft_atoi(argv[1]) * sizeof(int));
	mutexes = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	(*philos)->mutexes = mutexes;
	(*philos)->n_phil = ft_atoi(argv[1]);
	(*philos)->die = ft_atoi(argv[2]);
	(*philos)->eat = ft_atoi(argv[3]);
	(*philos)->sleep = ft_atoi(argv[4]);
	(*philos)->forks = *forks;
	gettimeofday(&(*philos)->created_at, NULL);
	if (argc == 6)
	{
		(*philos)->to_eat = ft_atoi(argv[5]);
		if ((*philos)->to_eat < 0)
			return (free(*philos), printf("ERROR: Invalid argument\n"), exit(2));
	}
	else
		(*philos)->to_eat = -1;
	init_others(philos, forks, &mutexes);
}
