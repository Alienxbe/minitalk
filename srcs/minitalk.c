/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:19:23 by mykman            #+#    #+#             */
/*   Updated: 2022/07/18 22:58:45 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** exit function with message
*/
void	ft_exit(char *str, int val)
{
	ft_printf("%s\n", str);
	exit(val);
}

/*
** Wrapper function for sigaction()
*/
void	ft_sig(int sig, int flag, void (*f)(int))
{
	t_sig	sa;

	sa.sa_flags = flag;
	sa.sa_handler = f;
	sigaction(sig, &sa, NULL);
}

/*
** Send data to a pid
**
** d:		the address of the data
** size:	the size of the data
** pid:		the pid to send the data
*/
void	send_data(size_t d, size_t size, pid_t pid)
{
	int	i;

	i = size * 8;
	while (--i >= 0)
	{
		if (d >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(SLEEP_BETWEEN_MSG);
	}
}

/*
** Receive and read data from a signal
**
** bit:		bit read from the signal
** size:	lenght of the data to be read (in bytes)
*/
size_t	read_data(unsigned char bit, size_t size)
{
	static size_t	bit_count;
	static size_t	n;
	size_t			ret;

	ret = 0;
	n = (n << 1) + bit;
	if (++bit_count == size * 8)
	{
		ret = n;
		n = 0;
		bit_count = 0;
	}
	return (ret);
}
