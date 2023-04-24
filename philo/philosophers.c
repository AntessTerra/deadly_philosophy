/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/24 14:58:50 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	alone(t_philo **philo)
{
	usleep((*philo)->die * 1000);
	printf("%-5d %-5s %-5s\n", (*philo)->die, "1", "\e[0;31mhas died\e[0m");
	free((*philo)->mutexes);
	free((*philo)->megaphone);
	free((*philo)->alive);
	free((*philo)->forks);
	free(*philo);
	exit(0);
}

void	odd_sleep(t_philo **philo)
{
	struct timeval	timenow;

	if ((*philo)->id % 2 == 0 && (*philo)->init_sleep)
	{
		gettimeofday(&timenow, NULL);
		pthread_mutex_lock((*philo)->megaphone);
		if ((*philo)->alive[0])
			printf("%-5lld %-5d \e[0;36m is sleeping \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		pthread_mutex_unlock((*philo)->megaphone);
		usleep((*philo)->sleep * 1000);
		(*philo)->init_sleep = 0;
		gettimeofday(&timenow, NULL);
		pthread_mutex_lock((*philo)->megaphone);
		if ((*philo)->alive[0])
			printf("%-5lld %-5d \e[0;32m is thinking \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		pthread_mutex_unlock((*philo)->megaphone);
	}
}

int	is_alive(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (!(*philo)->alive[0])
		return (0);
	if (timesince((*philo)->ate_last, timenow) >= (*philo)->die)
	{
		pthread_mutex_lock((*philo)->megaphone);
		if ((*philo)->alive[0])
		{
			(*philo)->alive[0] = 0;
			printf("%-5lld %-5d \e[0;31m died \e[0m\n",
				timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		}
		pthread_mutex_unlock((*philo)->megaphone);
		return (0);
	}
	return (1);
}

void	*thread_routine(void *data)
{
	struct s_philo	*philo;

	philo = (struct s_philo *) data;
	gettimeofday(&(*philo).ate_last, NULL);
	while (philo->alive[0])
	{
		odd_sleep(&philo);
		if (!do_eat(&philo))
			return (NULL);
		if (philo->n_ate == philo->to_eat)
			return (NULL);
		do_sleep(&philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				n;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;

	init_philo(argc, argv, &philos, &mutexes);
	if (philos[0].n_phil == 1)
		alone(&philos);
	pthread_mutex_init(philos->megaphone, NULL);
	n = -1;
	while (++n < philos[0].n_phil)
	{
		philos[n].id = n;
		philos[n].forks[n] = 1;
		pthread_mutex_init(&mutexes[n], NULL);
		pthread_create(&philos[n].thread, NULL, &thread_routine, &philos[n]);
	}
	n = -1;
	while (++n < philos[0].n_phil)
	{
		pthread_join(philos[n].thread, NULL);
		pthread_mutex_destroy(&mutexes[n]);
	}
	return (free(mutexes), free(philos->forks),
		pthread_mutex_destroy(philos->megaphone),
		free(philos->alive), free(philos->megaphone), free(philos), 0);
}
