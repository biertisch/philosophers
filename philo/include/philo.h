/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:07 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 15:46:07 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_0 "Invalid input: invalid number of arguments"
# define ERR_1 "Invalid input: invalid character"
# define ERR_2 "Invalid input: invalid value"
# define ERR_3 "Failed to allocate memory"
# define ERR_4 "Failed to initialize mutex"
# define ERR_5 "Failed to create thread"

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_sim			*sim;
}					t_philo;

typedef struct s_sim
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	pthread_mutex_t	sim_lock;
	int				sim_over;
	int				sim_mutex_init;
	pthread_mutex_t	print_lock;
	int				print_mutex_init;	
	pthread_mutex_t	*forks;
	int				fork_mutexes_init;
	t_philo			*philos;
	int				threads_created;
	int				meal_mutexes_init;	
}					t_sim;

int		validate_input(t_sim *sim, int argc, char **argv);
long	ft_atol(const char *s);
int		init_config(t_sim *sim, int argc, char **argv);
int		init_philos(t_sim *sim);
void	*routine(void *arg);
void	monitor(t_sim *sim);
void	print_status(t_philo *philo, char *msg);
long	get_time_ms(void);
void	sleep_ms(t_sim *sim, long msec);
int		error_exit(t_sim *sim, char *error_msg);
int		stop_simulation(t_sim *sim);
void	cleanup(t_sim *sim);

#endif