/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:17:15 by mykman            #+#    #+#             */
/*   Updated: 2022/07/20 15:13:51 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_var(pid_t *pid, int *len, int *i)
{
	ft_printf("\n\n* Finished reading from %d!\n\n", *pid);
	send_data(*len, sizeof(int), *pid);
	*pid = 0;
	*len = 0;
	*i = 0;
}

static void	handle_sig(int sig)
{
	static pid_t	pid;
	static int		len;
	static int		i;
	char			c;

	if (!pid)
		pid = read_data(sig == SIGUSR2, sizeof(pid_t));
	else if (!len)
		len = read_data(sig == SIGUSR2, sizeof(int));
	else
	{
		c = read_data(sig == SIGUSR2, sizeof(char));
		if (c)
		{
			ft_printf("%c", c);
			i++;
		}
		if (i == len)
			reset_var(&pid, &len, &i);
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		ft_exit("Usage: ./server", 1);
	ft_sig(SIGUSR1, SA_SIGINFO, &handle_sig);
	ft_sig(SIGUSR2, SA_SIGINFO, &handle_sig);
	ft_printf("Server opened on pid: %d\n\n", getpid());
	while (1)
		pause();
	return (0);
}
