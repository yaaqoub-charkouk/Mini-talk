/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:05 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/11 07:11:46 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_talk.h"

static t_list	*g_msj;

void	print_message(void)
{
	print_list(g_msj);
	ft_list_clear(&g_msj);
}

void	accumulate_message(t_list **last_node, char current_char)
{
	t_list	*new_node;

	new_node = ft_lstnew(current_char);
	if (!new_node)
		return ;
	if (g_msj)
	{
		if (*last_node)
		{
			(*last_node)->next = new_node;
			*last_node = (*last_node)->next;
		}
	}
	else
	{
		*last_node = new_node;
		g_msj = *last_node;
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int		seq = 0;
	static char		current_char = 0;
	static pid_t	client_pid;
	static t_list	*last_node;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		current_char = 0;
		seq = 0;
		ft_list_clear(&g_msj);
		last_node = NULL;
	}
	current_char = (current_char << 1) | (signal == SIGUSR2);
	seq++;
	if (seq == 8)
	{
		accumulate_message(&last_node, current_char);
		if (current_char == '\0')
			print_message();
		seq = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("The Server pid:\t%d\n", getpid());
	g_msj = NULL;
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1337)
		pause();
	return (0);
}
