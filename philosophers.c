/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/27 22:57:26 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void take_fork(t_philosophers *philo)
{
	uint64_t diff_time;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "\033[1;32mhas taken a fork");
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		pthread_mutex_lock(&philo->left->fork);
		printf("comer %llu\n", philo->time_to->eat / 1000);
		if(get_time() - philo->start > ((philo->time_to->eat + 10000) / 1000))
		{
			diff_time = get_time() - philo->start_think;
		}
		printf("pensar [%llu] %d\n", diff_time, philo->num);
		printf("tic toc [%lld]\n", philo->time_to->tic_toc);
		philo->time_to->tic_toc -= philo->start_think;
		printf("tic toc new [%lld]\n", philo->time_to->tic_toc);
		print_status(philo, "\033[1;32mhas taken a fork");
	}
}

void free_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
}

void eat_philo(t_philosophers *philo)
{
	take_fork(philo);
	if(philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		print_status(philo, "\033[1;33mis eating");
		philo->time_to->tic_toc = philo->time_to->die;
		usleep(philo->time_to->eat);
		free_fork(philo);
		philo->time_to->tic_toc -= philo->time_to->eat;	
	}
}

void	*start_philo(void *arg)
{
	t_philosophers *philo;
	t_philosophers *tmp_ph;


	philo = (t_philosophers *)arg;
	philo->time_to->tic_toc = (long long)(philo->time_to->die / 1000);
	philo->start_think = 0;
	
	if (philo->num % 2 == 0 || (philo->size_lst == (size_t)philo->num))
		usleep(philo->time_to->eat);
	while (philo->time_to->tic_toc > 0 && *philo->die == 0)
	{
		eat_philo(philo);
		if(philo->time_to->tic_toc > 0 && *philo->die == 0)
		{
			print_status(philo, "\033[1;34mis sleeping");
			usleep(philo->time_to->sleep);
			philo->time_to->tic_toc -= philo->time_to->sleep;
		}
		if(philo->time_to->tic_toc > 0 && *philo->die == 0)
		{
			print_status(philo, "\033[1;35mis thinking");
			philo->start_think = (uint64_t)(get_time() - philo->start);
			printf("*** --> pensar [%llu] %d\n", philo->start_think, philo->num);
			
		}
	}
	pthread_mutex_lock(philo->print_die);
	if (*philo->die == 0)
	{
		printf("%6llu %s \033[0;36m%2d  %s\n\033[0;37m", get_time() - philo->start, "ms",philo->num, "\033[1;31mis die");
		*philo->die = 1;
	}
	 pthread_mutex_unlock(philo->print_die);
	return(NULL);
}

void	create_philosophers(t_philosophers *lst_philos, int n_philo)
{
	int i, j;
	t_philosophers *tmp_ph;
	t_bool die;

	j = n_philo -1 ;
	die = 0;
	tmp_ph = lst_philos;
	i = 0;

	while(i < n_philo)
	{
		lst_philos->hilo = (pthread_t *)malloc(sizeof(pthread_t));
		lst_philos->size_lst = n_philo;
		lst_philos->die = &die;
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
	
	 while(n_philo--)
	{
		pthread_mutex_unlock(&lst_philos->fork);
		pthread_mutex_destroy(&lst_philos->fork);
		if (lst_philos->right)
		{
			pthread_join(*lst_philos->hilo, NULL);
			lst_philos = lst_philos->right;
			free(lst_philos->time_to);
			free(lst_philos);
		}
	}
	
}


t_philosophers *new_philo(int  num, t_time *time, struct timeval start, size_t size)
{
	t_philosophers	*philo;
	static pthread_mutex_t print;
	static pthread_mutex_t print_die;
	static t_bool die;

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
	philo->start_think = 0;
	philo->start= get_time();
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