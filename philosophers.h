/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:59:19 by krios-fu          #+#    #+#             */
/*   Updated: 2021/06/22 20:57:34 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_fork
{
	int			status;
	
}				t_fork;

typedef	struct s_philosophers
{
	struct s_philosophers	*r;
	struct s_philosophers	*l;
	struct s_fork			fork;
	int						num;
}			t_philosophers;

/* 
** functions utils
*/
int	ft_isdigit(int c);
int	min_atoi(char *str);

#endif