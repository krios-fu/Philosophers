/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:58:28 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/29 03:22:54 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	min_atoi(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += str[i] - '0';
		if (str[i + 1] != '\0')
			nb *= 10;
		else
			return (nb);
		i++;
	}
	return (-1);
}

void print_status(t_philosophers *philo, char *message)
{
	uint64_t	diff;

	diff = get_time() - philo->start;
	pthread_mutex_lock(philo->print);
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		printf("%6llu %s \033[1;36m%3d  %s\n\033[1;37m", diff, "ms",philo->num, message);
	}
	pthread_mutex_unlock(philo->print);
}

uint64_t get_time()
{
	static struct timeval	end;
	gettimeofday(&end, NULL);
	return((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000));
}