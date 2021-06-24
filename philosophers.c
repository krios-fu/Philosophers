/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:15:58 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/24 20:33:15 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void print_status(t_philosophers philo, char *message)
{
	struct timeval	end;
	int			diff;
	
	gettimeofday(&end, NULL);
	
	diff = ((end.tv_usec - philo.start.tv_usec) / 1000);

	// ft_putnbr_fd(diff, 1);
	// ft_putstr_fd(" ", 1);
	// ft_putnbr_fd(philo.num, 1);
	// ft_putstr_fd(" ", 1);
	// ft_putstr_fd(message, 1);
	// ft_putstr_fd("\n", 1);
	
	 printf("%d %d %s\n", diff, philo.num, message);
	
}
void eat_philo(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->left->fork);
	print_status(*philo, " has taken a fork");
	//write(1, "hola", 4);
	pthread_mutex_lock(&philo->fork);
	print_status(*philo, "has taken a fork");
	print_status(*philo, "is eating");
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


t_philosophers *new_philo(int  num, t_time *time, struct timeval start)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	if(!philo)
		return (NULL);
	philo->right = philo;
	philo->left = philo;
	philo->num = num;
	philo->time_to = time;
	philo->start.tv_usec = start.tv_usec;
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
	
	n_philo = min_atoi(argv[1]);
	i = 2;
	
	gettimeofday(&start, NULL);
	lst_philo = new_philo(1, new_time(miltomic(argv[2]),miltomic(argv[3]), miltomic(argv[4])), start);
	while (i <= n_philo)
	{
		add_philos(&lst_philo, new_philo(i, new_time(miltomic(argv[2]), miltomic(argv[3]), miltomic(argv[4])), start));
		i++;
	}

	create_philosophers(lst_philo, n_philo);
	return(0);
	
}

/*int main ()
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);

	printf("time start: [%d]\n", start.tv_usec);
	sleep(5);
	gettimeofday(&end, NULL);
	printf("time end: [%d]\n", end.tv_usec);
	printf("time diff: [%d]\n", (end.tv_usec - start.tv_usec));
	printf("time diff mil: [%.4f]\n", (float)(end.tv_usec - start.tv_usec) / 1000);
}*/