/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:05 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/04 07:17:47 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_talk.h"

void	signal_handler(int signal)
{
	static int	seq = 0;
	static char	current_char = 0;

	current_char = current_char << 1;
	if (signal == SIGUSR1)
		current_char = current_char | 0;
	if (signal == SIGUSR2)
		current_char = current_char | 1;
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
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
