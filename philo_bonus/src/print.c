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

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	sem_wait(philo->sim->sem_print);
	timestamp = get_time_ms() - philo->sim->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	if (ft_strncmp(msg, "died", 4) != 0)
		sem_post(philo->sim->sem_print);
}
