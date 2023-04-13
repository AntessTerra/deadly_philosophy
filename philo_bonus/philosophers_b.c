/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:45 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/13 18:21:16 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	alone(t_philo **philo)
{
	milisleep((*philo)->sleep);
	printf("%-5d %-5s %-5s\n", (*philo)->sleep, "1", "\e[0;31mhas died\e[0m");
	free((*philo)->alive);
	free(*philo);
	exit(0);
}

int	is_alive(t_philo **philo)
{
	struct timeval	timenow;

	gettimeofday(&timenow, NULL);
	if (!(*philo)->alive[0])
		return (0);
	if (timesince((*philo)->ate_last, timenow) >= (*philo)->die)
	{
		(*philo)->alive[0] = 0;
		printf("%-5lld %-5d \e[0;31m died \e[0m\n",
			timesince((*philo)->created_at, timenow), (*philo)->id + 1);
		return (0);
	}
	return (1);
}

void	*processs_routine(t_philo *philo)
{
	sem_t	*sem;

	sem = sem_open(SNAME, 0);
	gettimeofday(&(*philo).ate_last, NULL);
	while (philo->alive[0])
	{
		odd_sleep(&philo);
		if (!is_alive(&philo))
			return (NULL);
		do_eat(&philo, sem);
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

void	cutlery(t_philo *philos, int n)
{
	pid_t	pid;

	while (++n < philos[0].n_phil)
	{
		philos[n].id = n;
		pid = fork();
		if (pid == 0)
			processs_routine(&philos[n]);
		else if (pid < 0)
			perror("FAILED TO FORK IT UP\n");
	}
}

int	main(int argc, char **argv)
{
	int		n;
	t_philo	*philos;

	init_philo(argc, argv, &philos);
	if (philos[0].n_phil == 1)
		alone(&philos);
	sem_unlink(SNAME);
	philos->sem = sem_open(SNAME, O_CREAT, 0644, philos->n_phil);
	n = -1;
	cutlery(philos, n);
	n = -1;
	while (++n < philos[0].n_phil)
	{
		waitpid(0, NULL, 0);
	}
	return (free(philos->alive), sem_close(philos->sem),
		free(philos), kill(0, SIGKILL));
}
