/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:16 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:16 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	stop_simulation(t_sim *sim)
{
	int	status;

	pthread_mutex_lock(&sim->sim_lock);
	status = sim->sim_over;
	pthread_mutex_unlock(&sim->sim_lock);
	return (status);
}

static void	check_meal_completion(t_sim *sim)
{
	int		i;
	int		satisfied;
	long	now;

	i = 0;
	satisfied = 0;
	now = get_time_ms();
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (sim->philos[i].meals_eaten >= sim->required_meals)
			satisfied++;
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	if (satisfied == sim->philo_count)
	{
		pthread_mutex_lock(&sim->print_lock);
		printf("%ld All philosophers are satisfied\n", now - sim->start_time);
		pthread_mutex_unlock(&sim->print_lock);
		pthread_mutex_lock(&sim->sim_lock);
		sim->sim_over = 1;
		pthread_mutex_unlock(&sim->sim_lock);
	}
}

void	monitor(t_sim *sim)
{
	int		i;
	long	now;

	i = 0;
	now = get_time_ms();
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (now - sim->philos[i].last_meal >= sim->time_to_die)
		{
			pthread_mutex_unlock(&sim->philos[i].meal_lock);
			pthread_mutex_lock(&sim->sim_lock);
			sim->sim_over = 1;
			pthread_mutex_unlock(&sim->sim_lock);
			pthread_mutex_lock(&sim->print_lock);
			printf("%ld %d died\n", now - sim->start_time, sim->philos[i].id);
			pthread_mutex_unlock(&sim->print_lock);
			return ;
		}
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		i++;
	}
	if (sim->required_meals != -1)
		check_meal_completion(sim);
}
