/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:11:13 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/04 11:09:03 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_talk.h"

static int	g_ack_received = 0;

void	ack_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Acknowledgment received, exiting...\n");
		g_ack_received = 1;
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
		usleep(100);
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
	int	timeout;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid == -1)
			return (1);
		timeout = 3;
		signal(SIGUSR1, ack_handler);
		msj_to_signals(pid, av[2]);
		while (!g_ack_received && timeout >= 0)
		{
			usleep(500);
			timeout--;
		}
		return (ft_printf("Timeout: Acknowledgment not received .\n"), 1);
	}
	else
		return (ft_printf("Usage: <./client> <server_pid> <msj>"), 1);
	return (0);
}
