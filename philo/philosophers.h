/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:56:44 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/14 15:42:25 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eat;
	int				die;
	int				sleep;
	int				to_eat;
	int				n_phil;
	pthread_t		thread;
	pthread_mutex_t	mutex;
}				t_philo;

#endif
