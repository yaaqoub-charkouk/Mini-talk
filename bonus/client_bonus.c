/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:11:13 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/10 11:25:20 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk_bonus.h"

void	ack_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Acknowledgment received, exiting...\n");
		exit(EXIT_SUCCESS);
	}
}

void	char_to_signals(int pid, char c)
{
	int	window;

	window = 7;
	while (window >= 0)
	{
		if (((c >> window) & 1) == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		window--;
	}
}

void	msj_to_signals(int pid, char *msj)
{
	int	seq;

	seq = 0;
	while (msj[seq])
	{
		char_to_signals(pid, msj[seq]);
		seq++;
	}
	if (msj[seq] == '\0')
		char_to_signals(pid, '\0');
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid < 0 || kill(pid, 0) == -1)
			return (1);
		signal(SIGUSR1, ack_handler);
		msj_to_signals(pid, av[2]);
		while (1337)
			pause();
	}
	else
		return (ft_printf("Usage: <./client> <server_pid> <msj>"), 1);
	return (0);
}
