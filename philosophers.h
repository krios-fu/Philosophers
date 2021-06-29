/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:59:19 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/29 03:53:18 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>




typedef struct s_time
{
	useconds_t	die;
	useconds_t	eat;
	useconds_t	sleep;
	long long	tic_toc;
	int			count_eat;
	int			must_eat;
	int			*tmp_must_eat;
	
}				t_time;

typedef	int	t_bool;

typedef	struct s_philosophers
{
	struct s_philosophers	*right;
	struct s_philosophers	*left;
	struct s_time			*time_to;
	pthread_mutex_t			*print;
	pthread_mutex_t			*print_die;
	pthread_mutex_t			fork;
	pthread_t 				*hilo;
	uint64_t				start;
	uint64_t				start_think;
	t_bool					*die;
	size_t					size_lst;
	int						num;
	t_bool					think;


}			t_philosophers;

/* 
** functions utils
*/
int			ft_isdigit(int c);
int			min_atoi(char *str);
void		print_status(t_philosophers *philo, char *message);
uint64_t 	get_time();
int			check_arg (char *argv[]);

/* 
** Functions Put
*/

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

/* 
** Functions status
*/

void 	eat_philo(t_philosophers *philo);
void 	sleep_philo(t_philosophers *philo);
void 	think_philo(t_philosophers *philo);
void	die_philo(t_philosophers *philo);

/* 
** Functions fork_mutex
*/

void take_fork(t_philosophers *philo);
void free_fork(t_philosophers *philo);
t_time *new_time(char *argv[]);
t_philosophers *last_philo(t_philosophers *last_philo);

/* 
** Functions create_philo
*/

void	add_philos(t_philosophers **lst_philos, t_philosophers *new_elem);
t_philosophers *new_philo(int  num, t_time *time, struct timeval start, size_t size);
t_time *new_time(char *argv[]);
t_philosophers *last_philo(t_philosophers *last_philo);
useconds_t miltomic(char *time);

#endif