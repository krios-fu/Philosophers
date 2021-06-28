/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 02:35:35 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/28 03:13:11 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

t_philosophers *new_philo(int  num, t_time *time, struct timeval start, size_t size)
{
	t_philosophers			*philo;
	static t_bool			die;
	static pthread_mutex_t	print;
	static pthread_mutex_t	print_die;

	die = 0;
	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	if(!philo)
		return (NULL);
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&print_die, NULL);
	philo->print = &print;
	philo->print_die = &print_die;
	philo->right = philo;
	philo->left = philo;
	philo->num = num;
	philo->time_to = time;
	philo->die = &die;
	philo->start_think = (uint64_t)0;
	philo->start= get_time();
	philo->size_lst = size;
	return(philo);
}

t_time *new_time(char *argv[])
{
	t_time *new_time;

	new_time = (t_time *)malloc(sizeof(t_time));
	if(!new_time)
		return(NULL);
	new_time->die = miltomic(argv[2]);
	new_time->eat = miltomic(argv[3]);
	new_time->sleep = miltomic(argv[4]);
	if (argv[5])
		new_time->must_eat = min_atoi(argv[5]);
	new_time->count_eat = 0;
	return (new_time);
}

t_philosophers *last_philo(t_philosophers *last_philo)
{
	return(last_philo->left);
}

void	add_philos(t_philosophers **lst_philos, t_philosophers *new_elem)
{
	t_philosophers *tmp;

	tmp = last_philo(*lst_philos);

	
	(*lst_philos)->left = new_elem;
	tmp->right = new_elem;
	new_elem->right = (*lst_philos);
	new_elem->left = tmp;
}

useconds_t miltomic(char *time)
{
	useconds_t micro_sec;

	micro_sec = (min_atoi(time) * 1000);
	return (micro_sec);
}