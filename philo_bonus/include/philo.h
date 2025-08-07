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
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR_0 "Invalid input: invalid number of arguments"
# define ERR_1 "Invalid input: invalid character"
# define ERR_2 "Invalid input: invalid value"
# define ERR_3 "Failed to allocate memory"
# define ERR_4 "Failed to open semaphore"
# define ERR_5 "Failed to create child process"

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	int			holding_forks;
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
}			t_sim;

int		validate_input(t_sim *sim, int argc, char **argv);
long	ft_atol(const char *s);
int		init_config(t_sim *sim, int argc, char **argv);
int		create_children(t_sim *sim);
void	wait_for_children(t_sim *sim);
void	routine(t_philo *philo);
int		check_satisfaction(t_philo *philo);
int		check_death(t_philo *philo);
void	print_status(t_philo *philo, char *msg);
long	get_time_ms(void);
void	sleep_ms(t_philo *philo, long msec);
void	child_cleanup(t_philo *philo);
void	cleanup(t_sim *sim);
int		error_exit(t_sim *sim, char *error_msg);

#endif