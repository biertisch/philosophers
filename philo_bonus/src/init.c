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

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (error_exit(sim, philo, ERR_6));
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = sim->start_time;
	philo->sim = sim;
	init_philo_semaphore(philo);
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
	if (!init_sim_semaphores(sim))
		return (error_exit(sim, NULL, ERR_3));
	return (1);
}
