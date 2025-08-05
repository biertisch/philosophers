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

void	sleep_ms(t_sim *sim, long msec)
{
	long	start;
	long	now;
	long	last_check;

	if (msec <= 0)
		return ;
	start = get_time_ms();
	now = start;
	last_check = start;
	while (now - start < msec)
	{
		if (now - last_check >= 10)
		{
			if (stop_sim(sim))
				break ;
			last_check = now;
		}
		usleep(500);
		now = get_time_ms();
	}
}
