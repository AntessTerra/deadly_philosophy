/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:46:22 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/24 15:01:08 by jbartosi         ###   ########.fr       */
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

void	init_others_others(t_philo **philos, int i)
{
	(*philos)[i].n_phil = (*philos)[0].n_phil;
	(*philos)[i].die = (*philos)[0].die;
	(*philos)[i].eat = (*philos)[0].eat;
	(*philos)[i].sleep = (*philos)[0].sleep;
	(*philos)[i].to_eat = (*philos)[0].to_eat;
}

void	init_others(t_philo **philos, pthread_mutex_t **mutexes, int *forks)
{
	int				i;
	int				*alive;
	pthread_mutex_t	*megaphone;

	forks = malloc((*philos)->n_phil * sizeof(int));
	alive = malloc(1 * sizeof(int));
	alive[0] = 1;
	i = 0;
	(*philos)[0].forks = forks;
	(*philos)[0].n_ate = 0;
	(*philos)[0].alive = alive;
	(*philos)[0].init_sleep = 1;
	megaphone = malloc(1 * sizeof(pthread_mutex_t));
	(*philos)[0].megaphone = megaphone;
	while (++i < (*philos)[0].n_phil)
	{
		init_others_others(philos, i);
		(*philos)[i].alive = alive;
		(*philos)[i].init_sleep = 1;
		(*philos)[i].n_ate = 0;
		(*philos)[i].forks = forks;
		(*philos)[i].mutexes = *mutexes;
		(*philos)[i].megaphone = megaphone;
		gettimeofday(&(*philos)[i].created_at, NULL);
	}
}

void	init_philo(int argc, char **argv, t_philo **philos,
	pthread_mutex_t	**mutexes)
{
	static int		*forks;

	if (argc < 5 || argc > 6)
		return (printf("ERROR: Incorect number of arguments\n"), exit(1));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (printf("ERROR: Invalid argument\n"), exit(2));
	*philos = malloc((ft_atoi(argv[1]) * sizeof(t_philo))
			+ ft_atoi(argv[1]) * sizeof(int));
	*mutexes = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	(*philos)[0].mutexes = *mutexes;
	(*philos)[0].n_phil = ft_atoi(argv[1]);
	(*philos)[0].die = ft_atoi(argv[2]);
	(*philos)[0].eat = ft_atoi(argv[3]);
	(*philos)[0].sleep = ft_atoi(argv[4]);
	gettimeofday(&(*philos)[0].created_at, NULL);
	if (argc == 6)
	{
		(*philos)[0].to_eat = ft_atoi(argv[5]);
		if ((*philos)[0].to_eat < 0)
			return (free(*philos), printf("ERROR: Invalid argument\n"), exit(2));
	}
	else
		(*philos)[0].to_eat = -1;
	init_others(philos, mutexes, forks);
}
