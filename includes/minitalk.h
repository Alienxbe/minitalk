/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:26:06 by mykman            #+#    #+#             */
/*   Updated: 2023/11/14 13:49:34 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# include "ft_colors.h"
# include "ft_ctype.h"
# include "ft_memory.h"
# include "ft_printf.h"
# include "ft_string.h"
# include "ft_stdio.h"

# define SLEEP_BETWEEN_MSG	100

typedef struct sigaction	t_sig;

typedef struct s_data
{
	size_t			n;
	unsigned char	isread;
}	t_data;

void	ft_exit(char *str, int val);
void	ft_sig(int sig, int flag, void (*f)(int));
void	send_data(size_t d, size_t size, pid_t pid);
t_data	read_data(unsigned char bit, size_t size);

#endif
