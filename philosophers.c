/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/24 16:06:22 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void eat_philo(t_philosophers *philo)
{
	
	pthread_mutex_lock(&philo->left->fork);
	pthread_mutex_lock(&philo->fork);
	printf("Hilo %i\n", philo->num);
	usleep(philo->time_to->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
}

void	*start_philo(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;
	
	while(1)
	{
		//printf("--------\n");
		eat_philo(philo);
		usleep(philo->time_to->sleep);
	}
	return(arg);	
}

void	create_philosophers(t_philosophers *lst_philos, int n_philo)
{
	int i, j;
	t_philosophers *tmp_ph;


	j = n_philo -1 ;
	tmp_ph = lst_philos;
	i = 0;

	while(i < n_philo)
	{
		lst_philos->hilo = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_mutex_init(&lst_philos->fork, NULL);
		pthread_create(lst_philos->hilo, NULL, start_philo, (void *)lst_philos);
		lst_philos = lst_philos->right;
		i++;
	}

	while(j >= 0)
	{
		pthread_join(*tmp_ph->hilo, NULL);
		tmp_ph = tmp_ph->right;
		j--;
	}
	
}


t_philosophers *new_philo(int  num, t_time *time)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	if(!philo)
		return (NULL);
	philo->right = philo;
	philo->left = philo;
	philo->num = num;
	philo->time_to = time;
	return(philo);
}

t_time *new_time(useconds_t die, useconds_t eat, useconds_t sleep)
{
	t_time *new_time;

	new_time = (t_time *)malloc(sizeof(t_time));
	if(!new_time)
		return(NULL);
	new_time->die = die;
	new_time->eat = eat;
	new_time->sleep = sleep;
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

int main (int argc, char *argv[])
{
	t_philosophers *lst_philo;
	int n_philo;
	
	n_philo = min_atoi(argv[1]);
	int i;
	i = 2;
	
	lst_philo = new_philo(1, new_time(miltomic(argv[2]),miltomic(argv[3]), miltomic(argv[4])));
	while (i <= n_philo)
	{
		add_philos(&lst_philo, new_philo(i, new_time(miltomic(argv[2]), miltomic(argv[3]), miltomic(argv[4]))));
		i++;
	}

	create_philosophers(lst_philo, n_philo);
	return(0);
	
}
