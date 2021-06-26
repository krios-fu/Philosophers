/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/26 03:16:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"


void print_status(t_philosophers *philo, char *message)
{
	struct timeval	end;
	uint64_t	diff;
	
	pthread_mutex_lock(philo->print);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000) - philo->start;
	philo->time_to->tic_toc -= diff;
	printf("%3llu %s \033[0;36m%2d  %s\n\033[0;37m", diff, "ms",philo->num, message);
	pthread_mutex_unlock(philo->print);
}

void take_fork(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "\033[0;32mhas taken a fork");
	pthread_mutex_lock(&philo->left->fork);
	print_status(philo, "\033[0;32mhas taken a fork");
}

void free_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
}

void eat_philo(t_philosophers *philo)
{
	take_fork(philo);
	print_status(philo, "\033[0;33mis eating");
	philo->time_to->tic_toc = philo->time_to->die;
	//printf("%d %d", philo->num, philo->time_to->eat);
	usleep(philo->time_to->eat);
	free_fork(philo);
}

void	*start_philo(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;
	
	philo->time_to->tic_toc = philo->time_to->die;

	// printf("%d\n", philo->time_to->tic_toc);
	if (philo->num % 2 == 0 || (philo->size_lst == (size_t)philo->num))
	{
		print_status(philo, "\033[0;35mis thinking");
		// usleep(philo->time_to->eat);
	}
	while(philo->time_to->tic_toc > 0)
	{
		eat_philo(philo);
		
		print_status(philo, "\033[0;34mis sleeping");
		usleep(philo->time_to->sleep);		
		print_status(philo, "\033[0;35mis thinking");

		//printf("[[[%llu]]]\n", philo->time_to->tic_toc);
	}

	print_status(philo, "\033[0;31mis died");	
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


t_philosophers *new_philo(int  num, t_time *time, struct timeval start, size_t size)
{
	t_philosophers	*philo;
	static pthread_mutex_t status;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	if(!philo)
		return (NULL);
	pthread_mutex_init(&status, NULL);
	philo->print = &status;
	philo->right = philo;
	philo->left = philo;
	philo->num = num;
	philo->time_to = time;
	philo->start= (start.tv_sec * (uint64_t)1000) + (start.tv_usec / 1000);
	philo->size_lst = size;
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
	struct timeval start;
	int n_philo;
	int i;
	(void)argc;
	
	n_philo = min_atoi(argv[1]);
	i = 2;
	
	gettimeofday(&start, NULL);
	lst_philo = new_philo(1, new_time(miltomic(argv[2]), miltomic(argv[3]), miltomic(argv[4])), start, n_philo);
	while (i <= n_philo)
	{
		add_philos(&lst_philo, new_philo(i, new_time(miltomic(argv[2]), miltomic(argv[3]), miltomic(argv[4])), start, n_philo));
		i++;
	}
	create_philosophers(lst_philo, n_philo);
	return(0);
	
}