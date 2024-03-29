/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:17:15 by mykman            #+#    #+#             */
/*   Updated: 2023/11/15 19:06:07 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_var(t_data *pid, t_data *len, int *i, unsigned char **str)
{
	write(STDOUT_FILENO, *str, len->n);
	ft_printf(FT_GREEN "\n\n* Finished reading from %d!\n\n" FT_RESETCOL, pid->n);
	send_data(len->n, sizeof(int), pid->n);
	ft_bzero(pid, sizeof(t_data));
	ft_bzero(len, sizeof(t_data));
	*i = 0;
	free(*str);
	*str = NULL;
}

static void	handle_sig(int sig)
{
	static t_data			pid;
	static t_data			len;
	static int				i;
	static unsigned char	*str;
	t_data					c;

	if (!pid.isread)
		pid = read_data(sig == SIGUSR2, sizeof(pid_t));
	else if (!len.isread)
		len = read_data(sig == SIGUSR2, sizeof(int));
	else
	{
		if (!str)
		{
			str = malloc(sizeof(char) * len.n);
			if (!str)
				ft_exit("Allocation error", 1);
		}
		c = read_data(sig == SIGUSR2, sizeof(char));
		if (c.isread)
			str[i++] = (unsigned char)c.n;
	}
	if (len.isread && i == (int)len.n)
		reset_var(&pid, &len, &i, &str);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		ft_exit("Usage: ./server", 1);
	ft_sig(SIGUSR1, SA_SIGINFO, &handle_sig);
	ft_sig(SIGUSR2, SA_SIGINFO, &handle_sig);
	ft_printf(FT_YELLOW "Server opened on pid: %d\n\n" FT_RESETCOL, getpid());
	while (1)
		pause();
	return (0);
}
