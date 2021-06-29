/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:04:45 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/29 23:03:38 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	loop_must_eat(t_philosophers *philo)
{
	while (*philo->time_to->tmp_must_eat < philo->size_lst)
	{
		eat_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
		sleep_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
		think_philo(philo);
		if (*philo->time_to->tmp_must_eat == philo->size_lst)
			break ;
	}
}

void	loop_without_must_eat(t_philosophers *philo)
{
	while (1)
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
		if (philo->time_to->tic_toc < 0 || *philo->die == 1)
		{
			free_fork(philo);
			break ;
		}
	}
}
