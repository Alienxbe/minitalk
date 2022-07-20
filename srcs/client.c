/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:26:06 by mykman            #+#    #+#             */
/*   Updated: 2022/07/20 15:14:08 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_string(char *str, pid_t pid)
{
	if (!str)
		return ;
	while (*str)
		send_data(*str++, sizeof(char), pid);
}

static void	handle_sig(int sig)
{
	int	len;

	len = read_data(sig == SIGUSR2, sizeof(int));
	if (len)
	{
		ft_printf("Server has read %d characters\n", len);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		ft_exit("Usage: ./client <pid> <message>", 1);
	server_pid = ft_atoi(argv[1]);
	ft_sig(SIGUSR1, SA_SIGINFO, &handle_sig);
	ft_sig(SIGUSR2, SA_SIGINFO, &handle_sig);
	send_data(getpid(), sizeof(pid_t), server_pid);
	send_data(ft_strlen(argv[2]), sizeof(int), server_pid);
	send_string(argv[2], server_pid);
	while (1)
		pause();
	return (0);
}
