/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 02:12:39 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/28 02:13:18 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void take_fork(t_philosophers *philo)
{
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		pthread_mutex_lock(&philo->fork);
		print_status(philo, "\033[1;32mhas taken a fork");
		if(philo->time_to->tic_toc > 0 && *philo->die == 0)
		{
			pthread_mutex_lock(&philo->left->fork);
			if(get_time() - philo->start > ((philo->time_to->eat + 10000) / 1000))
				philo->time_to->tic_toc -= ((get_time() - philo->start) - philo->start_think) * 1000;
			print_status(philo, "\033[1;32mhas taken a fork");
		}
	}
}

void free_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
}