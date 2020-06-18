/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:36:26 by fernando          #+#    #+#             */
/*   Updated: 2020/06/18 20:51:48 by fernando         ###   ########.fr       */
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
	pthread_mutex_t	fork;
	pthread_mutex_t	*state;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*next;
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