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

static int	match(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	sem_wait(philo->sim->sem_print);
	timestamp = get_time_ms() - philo->sim->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	if (!match(msg, "died"))
		sem_post(philo->sim->sem_print);
}
