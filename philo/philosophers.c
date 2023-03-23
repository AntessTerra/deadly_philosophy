/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/19 16:50:46 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	alone(t_philo **philo)
{
	milisleep((*philo)->sleep);
	printf("%-5d %-5s %-5s\n", (*philo)->sleep, "1", "\e[0;31mhas died\e[0m");
	free(*philo);
	exit(0);
}

void	odd_sleep(t_philo **philo)
{
	struct timeval	timenow;

	if ((*philo)->id % 2 == 0 && (*philo)->init_sleep)
	{
		gettimeofday(&timenow, NULL);
		printf("%-5lld %-5d \e[0;96m is sleeping \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id);
		milisleep((*philo)->sleep);
		(*philo)->init_sleep = 0;
	}
}

int	is_alive(t_philo **philo)
{
	struct timeval	timenow;
	int				id;

	id = (*philo)->id;
	gettimeofday(&timenow, NULL);
	if (!(*philo)->alive)
		return (0);
	if (timesince((*philo)->ate_last, timenow) >= (*philo)->die)
	{
		printf("%-5lld %-5d \e[0;31m has died \e[0m\n",
			timesince((*philo)->ate_last, timenow), (*philo)->id);
		(*philo)->alive = 0;
		return (0);
	}
	return (1);
}

void	*thread_routine(void *data)
{
	struct s_philo	*philo;
	struct timeval	timenow;

	philo = (struct s_philo *) data;
	gettimeofday(&(*philo).ate_last, NULL);
	while (philo->alive)
	{
		odd_sleep(&philo);
		if (!is_alive(&philo))
			return (NULL);
		do_eat(&philo);
		gettimeofday(&(*philo).ate_last, NULL);
		do_sleep(&philo);
		if (!is_alive(&philo))
			return (NULL);
		do_think(&philo);
		if (!is_alive(&philo) || philo->n_ate == philo->to_eat)
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			n;
	int			*forks;
	t_philo		*philos;

	init_philo(argc, argv, &philos, &forks);
	if (philos[0].n_phil == 1)
		alone(&philos);
	n = -1;
	while (++n < philos[0].n_phil)
	{
		philos[n].id = n + 1;
		pthread_mutex_init(&philos[n].mutexes[n], NULL);
		pthread_create(&philos[n].thread, NULL, thread_routine, &philos[n]);
	}
	n = -1;
	while (++n < philos[0].n_phil)
		pthread_join(philos[n].thread, NULL);
	n = -1;
	while (++n < philos[0].n_phil)
		pthread_mutex_destroy(&philos[n].mutexes[n]);
	return (free(philos->mutexes), free(philos), free(forks), 0);
}
