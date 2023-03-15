/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:46:22 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/15 16:33:17 by jbartosi         ###   ########.fr       */
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
