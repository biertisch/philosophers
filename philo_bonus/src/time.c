/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:20:24 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:24 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	sleep_ms(t_philo *philo, long msec)
{
	long	start;

	if (msec <= 0)
		return ;
	start = get_time_ms();
	while (!check_death(philo) && get_time_ms() - start < msec)
		usleep(500);
}
