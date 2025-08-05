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

static void	assign_forks(t_sim *sim, int i)
{
	if (i == sim->philo_count - 1)
	{
		sim->philos[i].first_fork = &sim->forks[i];
		sim->philos[i].second_fork = &sim->forks[(i + 1) % sim->philo_count];
	}
	else
	{
		sim->philos[i].first_fork = &sim->forks[(i + 1) % sim->philo_count];
		sim->philos[i].second_fork = &sim->forks[i];
	}
}

int	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->philo_count);
	if (!sim->philos)
		return (error_exit(sim, ERR_7));
	i = 0;
	while (i < sim->philo_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].sim = sim;
		assign_forks(sim, i);
		if (pthread_mutex_init(&sim->philos[i].meal_lock, NULL) != 0)
			return (error_exit(sim, ERR_8));
		sim->meal_mutexes_init++;
		if (pthread_create(&sim->philos[i].thread, NULL, &routine,
				&sim->philos[i]) != 0)
			return (error_exit(sim, ERR_8));
		sim->threads_created++;
		i++;
	}
	return (1);
}

int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	if (!sim->forks)
		return (error_exit(sim, ERR_5));
	i = 0;
	while (i < sim->philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i++], NULL) == 0)
			sim->fork_mutexes_init++;
		else
			return (error_exit(sim, ERR_6));
	}
	return (1);
}

int	init_config(t_sim *sim, int argc, char **argv)
{
	sim->philo_count = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	sim->required_meals = -1;
	if (argc == 6)
		sim->required_meals = ft_atol(argv[5]);
	sim->sim_over = 1;
	if (pthread_mutex_init(&sim->sim_lock, NULL) == 0)
		sim->sim_mutex_init++;
	else
		return (error_exit(sim, ERR_3));
	if (pthread_mutex_init(&sim->print_lock, NULL) == 0)
		sim->print_mutex_init++;
	else
		return (error_exit(sim, ERR_3));
	sim->start_time = get_time_ms();
	if (sim->start_time < 0)
		return (error_exit(sim, ERR_4));
	return (1);
}
