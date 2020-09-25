/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 15:37:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/25 10:58:28 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct		s_args
{
	pid_t			*pid;
	sem_t			*meals;
	sem_t			*forks;
    pthread_t       tid1;
	pthread_t		tid2;
	int				nb_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long			t_start;
	int				nb_eat;
	long			last_meal;
	int				meal_cnt;
	int				who;
	int				flag;
	int				kill;
}					t_args;

long	ft_time(void);
int     ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_check_args(int ac, char **av);
void	ft_putstr(char *s);

void	ft_message(long time, int who, char *what);



#endif