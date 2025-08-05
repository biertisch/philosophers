/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:18 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 16:48:18 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_philo(t_sim *sim, int i)
{
	t_philo	*philo;
	char	*sem_name;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (error_exit(sim, philo, ERR_6));
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = sim->start_time;
	philo->sim = sim;
	sem_name = get_sem_meal_name(philo->id);
	if (!sem_name)
		return (error_exit(sim, philo, ERR_6));
	sem_unlink(sem_name);
	philo->sem_meal = sem_open(sem_name, O_CREAT | O_EXCL, 0666, 1);
	if (philo->sem_meal == SEM_FAILED)
	{
		free(sem_name);
		return (error_exit(sim, philo, ERR_7));
	}
	sem_unlink(sem_name);
	free(sem_name);
	routine(philo);
	exit(3);
}

int	create_children(t_sim *sim)
{
	int		i;
	pid_t	pid;

	sim->philo_pid = malloc(sizeof(pid_t) * sim->philo_count);
	if (!sim->philo_pid)
		return (error_exit(sim, NULL, ERR_4));
	i = 0;
	while (i < sim->philo_count)
	{
		pid = fork();
		if (pid == -1)
			return (error_exit(sim, NULL, ERR_5));
		else if (pid == 0)
			init_philo(sim, i);
		sim->philo_pid[i] = pid;
		i++;
	}
	return (1);
}

static int	init_semaphores(t_sim *sim)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_over");
	sim->sem_forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 0666,
		sim->philo_count);
	if (sim->sem_forks == SEM_FAILED)
		return (0);
	sim->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0666, 1);
	if (sim->sem_print == SEM_FAILED)
	{
		sem_unlink("/sem_forks");
		return (0);
	}
	sim->sem_over = sem_open("/sem_over", O_CREAT | O_EXCL, 0666, 1);
	if (sim->sem_over == SEM_FAILED)
	{
		sem_unlink("/sem_forks");
		sem_unlink("/sem_print");
		return (0);
	}
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_over");
	return (1);
}

int	init_config(t_sim *sim, int argc, char **argv)
{
	sim->philo_count = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	sim->start_time = get_time_ms();
	sim->required_meals = -1;
	if (argc == 6)
		sim->required_meals = ft_atol(argv[5]);
	if (!init_semaphores(sim))
		return (error_exit(sim, NULL, ERR_3));
	return (1);
}
