/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-19 16:35:40 by speladea          #+#    #+#             */
/*   Updated: 2024-10-19 16:35:40 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit_is_received;

void	ft_send_char(int pid, char character)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_bit_is_received = 0;
		if ((character >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_is_received == 0)
			usleep(42);
	}
}

void	ft_send_string(int pid, char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		ft_send_char(pid, string[i]);
		i++;
	}
	ft_send_char(pid, '\0');
}

void	ft_server_signal(int signal)
{
	if (signal == SIGUSR1)
		g_bit_is_received = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("\nString received! :)\n\n");
		exit(EXIT_SUCCESS);
	}
}

void	ft_errors(int argc, char *argv[])
{
	int	check_pid;

	if (argc != 3)
	{
		ft_printf("\n/!\\ ERROR /!\\\n\nUsage: ./client (SERVER_PID) (STRING)\n");
		exit(EXIT_FAILURE);
	}
	check_pid = ft_atoi(argv[1]);
	if (kill(check_pid, 0) < 0 || check_pid == 0 || check_pid == -1)
	{
		ft_printf("\n/!\\ ERROR /!\\\n\nWrong PID!\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	ft_errors(argc, argv);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, &ft_server_signal);
	signal(SIGUSR2, &ft_server_signal);
	ft_send_string(pid, argv[2]);
}
