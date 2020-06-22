/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:36:26 by fernando          #+#    #+#             */
/*   Updated: 2020/06/22 15:30:30 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

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
	sem_t			*forks;
	sem_t			*meals;
	sem_t			*death;
    pthread_t       tid;
	int				nb_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long			t_start;
	int				nb_eat;
	long			last_meal;
	int				meal_cnt;
	int				who;
}					t_args;

long	ft_time(void);
int     ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_check_args(int ac, char **av);
void	ft_putstr(char *s);

void	ft_message(long time, int who, char *what);



#endif