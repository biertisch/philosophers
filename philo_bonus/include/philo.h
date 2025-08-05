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
# define ERR_3 "Failed to initialize configuration (failed to open semaphore)"
# define ERR_4 "Failed to initialize philosophers (failed to allocate memory)"
# define ERR_5 "Failed to initialize philosophers (failed to create process)"
# define ERR_6 "Failed to initialize philosophers (failed to allocate memory)"
# define ERR_7 "Failed to initialize philosophers (failed to open semaphore)"
# define ERR_8 "Failed to initialize philosophers (failed to create thread)"
# define ERR_9 "Failed to initialize philosophers (failed to detach thread)"

typedef struct s_sim
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		required_meals;
	long	start_time;
	pid_t	*philo_pid;
	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	*sem_over;
	sem_t	*sem_dead;
}			t_sim;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	sem_t		*sem_meal;
	pthread_t	death_monitor;
	pthread_t	end_monitor;
	t_sim		*sim;
}				t_philo;

int		validate_input(t_sim *sim, int argc, char **argv);
long	ft_atol(const char *s);
int		init_config(t_sim *sim, int argc, char **argv);
int		create_children(t_sim *sim);
void	routine(t_philo *philo);
int		create_monitor_threads(t_philo *philo);
void	*monitor_death(void *arg);
void	*monitor_end(void *arg);
char	*get_sem_meal_name(int philo_id);
void	print_status(t_philo *philo, char *msg);
void	sleep_ms(long msec);
long	get_time_ms(void);
void	clean_philo(t_philo *philo);
void	clean_sim(t_sim *sim);
int		error_exit(t_sim *sim, t_philo *philo, char *error_msg);

#endif