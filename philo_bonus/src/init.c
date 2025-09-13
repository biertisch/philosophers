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

static void	launch_philo(t_sim *sim, int i)
{
	t_philo	*philo;

	philo = &sim->philos[i];
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = sim->start_time;
	philo->holding_forks = 0;
	philo->sim = sim;
	routine(philo);
	exit(2);
}

void	create_children(t_sim *sim)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < sim->philo_count)
	{
		pid = fork();
		if (pid == -1)
			error_exit(sim, ERR_5);
		else if (pid == 0)
			launch_philo(sim, i);
		sim->philo_pid[i] = pid;
		i++;
	}
}

static int	init_semaphores(t_sim *sim)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sim->sem_forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 0666,
			sim->philo_count);
	if (sim->sem_forks == SEM_FAILED)
		return (0);
	sim->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0666, 1);
	if (sim->sem_print == SEM_FAILED)
		return (0);
	return (1);
}

static int	allocate_memory(t_sim *sim)
{
	sim->philo_pid = malloc(sizeof(pid_t) * sim->philo_count);
	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (!sim->philo_pid || !sim->philos)
		return (0);
	return (1);
}

void	init_config(t_sim *sim, int argc, char **argv)
{
	sim->philo_count = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	sim->required_meals = -1;
	if (argc == 6)
		sim->required_meals = ft_atol(argv[5]);
	sim->start_time = get_time_ms();
	if (!allocate_memory(sim))
		error_exit(sim, ERR_3);
	if (!init_semaphores(sim))
		error_exit(sim, ERR_4);
}
