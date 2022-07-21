/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykman <mykman@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:26:06 by mykman            #+#    #+#             */
/*   Updated: 2022/07/20 15:13:59 by mykman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

# define SLEEP_BETWEEN_MSG	300

typedef struct sigaction	t_sig;

void	ft_exit(char *str, int val);
void	ft_sig(int sig, int flag, void (*f)(int));
void	send_data(size_t d, size_t size, pid_t pid);
size_t	read_data(unsigned char bit, size_t size);

#endif
