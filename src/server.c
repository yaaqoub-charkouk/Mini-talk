/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:05 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/07 07:35:44 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_talk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	seq = 0;
	static char	current_char = 0;
	static pid_t		client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		current_char = 0;
		seq = 0;
	}
	current_char = (current_char << 1) | (signal == SIGUSR2);
	seq++;
	if (seq == 8)
	{
		write (1, &current_char, 1);
		if (current_char == '\0')
			write(1, "\n", 1);
		seq = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("The Server pid:\t%d\n", getpid());
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}