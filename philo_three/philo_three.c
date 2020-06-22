/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 15:37:45 by fjimenez          #+#    #+#             */
/*   Updated: 2020/06/22 15:10:43 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*meal_loop(void *ptr)
{
	t_args	*s;
	int		i;

	s = (t_args *)ptr;
	i = -1;
	while (++i < s->nb_phi)
		sem_wait(s->meals);
	i = 0;
	while (i < s->nb_phi)
		kill(s->pid[i++], SIGTERM);
	free(s->pid);
	sem_unlink("forks");
	sem_unlink("meals");
	exit(0);
	return (NULL);
}

void	*death_loop(void *ptr)
{
	t_args	*s;
	int i;
	int check;

	s = (t_args *)ptr;
	check = 1;
	while (1)
	{
		if (ft_time() - s->last_meal > s->t_die)
		{
			ft_message(s->t_start, s->who, "died");
			i = 0;
			while (i < s->nb_phi)
				kill(s->pid[i++], SIGTERM);
			sem_close(s->forks);
			sem_close(s->meals);
			sem_unlink("forks");
			sem_unlink("meals");
			free(s->pid);
			exit(0);
		}
		else if (s->meal_cnt >= s->nb_eat && check)
		{
			sem_post(s->meals);
			check = 0;
		}
	}
	return (NULL);
}

void	makeActions(t_args s)
{	
	pthread_create(&s.tid1, NULL, death_loop, &s);
    while (1)
	{
		sem_wait(s.forks);
		ft_message(s.t_start, s.who, "has taken a fork");
		ft_message(s.t_start, s.who, "has taken a fork");
		s.last_meal = ft_time();
		ft_message(s.t_start, s.who, "is eating");
		usleep(s.t_eat * 1000);
		sem_post(s.forks);
		ft_message(s.t_start, s.who, "is sleeping");
		usleep(s.t_sleep * 1000);
		ft_message(s.t_start, s.who, "is thinking");
		s.meal_cnt++;
		if (s.meal_cnt == s.nb_eat)
			sem_wait(s.forks);
	}
}

void philo_three(t_args s)
{
	int i;

	if (!(s.pid = malloc(sizeof(pid_t) * s.nb_phi)))
		return ;
	i = -1;
	while (++i < s.nb_phi)
	{
		s.pid[i] = fork();
		if (s.pid[i] == 0)
		{
			s.who = i + 1;
			makeActions(s);
			i = s.nb_phi;
		}
	}
	if (s.nb_eat > -1)
		pthread_create(&s.tid1, NULL, meal_loop, &s);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < s.nb_phi)
		kill(s.pid[i++], SIGTERM);
	free(s.pid);
	sem_close(s.forks);
	sem_close(s.meals);
	sem_unlink("forks");
	sem_unlink("meals");
}

int main(int ac, char **av)
{
    t_args s;
    
    if (!ft_check_args(ac, av))
		return (1);
	s.forks = s.forks;
	s.meals = s.meals;
	s.nb_phi = ft_atoi(av[1]);
	s.t_die = ft_atoi(av[2]);
	s.t_eat = ft_atoi(av[3]);
	s.t_sleep = ft_atoi(av[4]);
	s.t_start = ft_time();
	s.nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	s.last_meal = s.t_start;
	s.meal_cnt = 0;
	sem_unlink("forks");
	sem_unlink("meals");
	s.forks = sem_open("forks", O_CREAT, S_IRWXU, (ft_atoi(av[1]) / 2));
	s.meals = sem_open("meals", O_CREAT, S_IRWXU, 0); 
	philo_three(s);
    return (0);
}