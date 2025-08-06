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

# include <fcntl.h> 
# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR_0 "Invalid input (invalid number of arguments)"
# define ERR_1 "Invalid input (invalid character)"
# define ERR_2 "Invalid input (invalid value)"
# define ERR_3 "Failed to allocate memory"
# define ERR_4 "Failed to open semaphore"
# define ERR_5 "Failed to create child process"
# define ERR_6 "Failed to create monitor thread"
# define STATUS_DEAD 0
# define STATUS_SATISFIED 1

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	int			dead;
	int			satisfied;
	pthread_t	monitor;
	sem_t		*sem_meal;
	sem_t		*sem_status;
	t_sim		*sim;
}				t_philo;

typedef struct s_sim
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		required_meals;
	long	start_time;
	pid_t	*philo_pid;
	t_philo	*philos;
	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	**sem_meal;
	sem_t	**sem_status;
}			t_sim;

int		validate_input(t_sim *sim, int argc, char **argv);
long	ft_atol(const char *s);
int		init_config(t_sim *sim, int argc, char **argv);
int		init_semaphores(t_sim *sim);
int		create_children(t_sim *sim);
void	routine(t_philo *philo);
int		create_monitor_thread(t_philo *philo);
int		get_status(t_philo *philo, int type);
void	set_status(t_philo *philo, int type);
void	print_status(t_philo *philo, char *msg);
void	sleep_ms(long msec);
long	get_time_ms(void);
void	wait_for_children(t_sim *sim);
void	child_cleanup(t_philo *philo);
void	cleanup(t_sim *sim);
int		error_exit(t_sim *sim, char *error_msg);

#endif