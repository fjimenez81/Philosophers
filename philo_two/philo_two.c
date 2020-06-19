/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:36:48 by fernando          #+#    #+#             */
/*   Updated: 2020/06/19 20:55:30 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*meal_loop(void *ptr)
{
	t_args	*s;
	int		i;

	s = (t_args *)ptr;
	i = -1;
	while (++i < s->nb_phi)
		sem_wait(s->meals);
	sem_post(s->death);
	return (NULL);
}

void	*death_loop(void *ptr)
{
	t_args	*s;
	int		alive;

	s = (t_args *)ptr;
	alive = 1;
	while (1)
	{
		if (ft_time() - s->last_meal >= s->t_die && alive)
		{
			ft_message(s->t_start, s->who, "has died");
			sem_post(s->death);
			alive = 0;
			sem_close(s[0].death);
			sem_close(s[0].forks);
			sem_close(s[0].meals);
			sem_unlink("forks");
			sem_unlink("death");
			sem_unlink("meals");
			free(s);
			exit (0);
		}
		else if (s->meal_cnt >= s->nb_eat && s->flag)
		{
			sem_post(s->meals);
			s->flag = 0;
		}
	}
	return (NULL);
}

void *makeActions(void *param)
{
    t_args		*s;

	s = (t_args *)param;
	pthread_create(&s->tid, NULL, death_loop, s);
    while (1)
	{
		sem_wait(s->forks);
		ft_message(s->t_start, s->who, "has taken a fork");
		ft_message(s->t_start, s->who, "has taken a fork");
		s->last_meal = ft_time();
		ft_message(s->t_start, s->who, "is eating");
		usleep(s->t_eat * 1000);
		s->meal_cnt++;
		sem_post(s->forks);
		ft_message(s->t_start, s->who, "is sleeping");
		usleep(s->t_sleep * 1000);
		ft_message(s->t_start, s->who, "is thinking");
		if (s->meal_cnt == s->nb_eat)
		{
			s->flag = 1;
			break ;
		}
	}
	return (NULL);
}

void philo_two(t_args *s)
{
	sem_t		*death;
	int i;
	
	sem_unlink("death");
	death = sem_open("death", O_CREAT, S_IRWXU, 0);
	i = 0;
	while (i < s[0].nb_phi)
	{
		s[i].death = death;
		s[i].last_meal = s[i].t_start;
		s[i].meal_cnt = 0;
		s[i].who = i + 1;
		pthread_create(&s->tid, NULL, makeActions, &s[i++]);
	}
	if (s[0].nb_eat > -1)
		pthread_create(&s->tid, NULL, meal_loop, &s[0]);
	sem_wait(death);
	/*sem_close(s[0].death);
	sem_close(s[0].forks);
	sem_close(s[0].meals);
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("death");*/
	//free(s);
	
}

int main(int ac, char **av)
{
    t_args *s;
    
    if (!ft_check_args(ac, av) ||
        !(s = malloc(sizeof(t_args) * ft_atoi(av[1]))))
		return (1);
	sem_unlink("forks");
	sem_unlink("meals");
	s[0].forks = sem_open("forks", O_CREAT, S_IRWXU, (ft_atoi(av[1]) / 2));
	s[0].meals = sem_open("meals", O_CREAT, S_IRWXU, 0);
    int i = -1;
    while(++i < ft_atoi(av[1]))
    {
		s[i].forks = s[0].forks;
		s[i].meals = s[0].meals;
		s[i].nb_phi = ft_atoi(av[1]);
		s[i].t_die = ft_atoi(av[2]);
		s[i].t_eat = ft_atoi(av[3]);
		s[i].t_sleep = ft_atoi(av[4]);
		s[i].t_start = ft_time();
		s[i].nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
        
		
    }
	philo_two(s);
    return (0);
}