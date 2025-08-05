/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:46:45 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/29 17:46:45 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!stop_sim(philo->sim))
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		timestamp = get_time_ms() - philo->sim->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
		pthread_mutex_unlock(&philo->sim->print_lock);
	}
}
