/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:37:48 by kostya            #+#    #+#             */
/*   Updated: 2021/11/02 16:45:29 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include "../inc/color.h"

static pid_t	ft_atoi(const char *str);
static int		send_message(const char *message, pid_t pid);
static void		done(int signum);
static void		ft_info(void);

volatile sig_atomic_t	g_response = 1;

int	main(int argc, char *const *argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, ERROR "[FAIL]" TERM_WHITE " wrong arguments\n", 0x25);
		ft_info();
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, ERROR "[FAIL]" TERM_WHITE " wrong PID format\n", 0x26);
		ft_info();
		return (1);
	}
	signal(SIGUSR1, done);
	signal(SIGUSR2, done);
	if (send_message(argv[2], pid))
		return ((int)write(1, ERROR "[FAIL]" TERM_WHITE " wrong pid\n", 0x1f));
	return (0);
}

static pid_t	ft_atoi(const char *str)
{
	pid_t	ans;

	ans = 0;
	while (*str >= '0' && *str <= '9')
		ans = ans * 10 + *str++ - '0';
	return (ans);
}

static int	send_message(const char *message, pid_t pid)
{
	static int		dsig = SIGUSR1 - SIGUSR2;
	unsigned char	byte;
	uint			cnt;

	while (1)
	{
		byte = *message;
		cnt = 0;
		while (cnt < 8)
		{
			g_response = 0;
			if (kill(pid, (int)((byte >> cnt) & 0x1u) *dsig + SIGUSR2))
				return (1);
			while (!g_response)
			{
			}
			if (g_response == SIGUSR2)
				write(1, OK "[ OK ]" TERM_WHITE " message sent "OK"successfully"
					RESET "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 0x38);
			++cnt;
		}
		if (!*message++)
			break ;
	}
	return (0);
}

static void	done(int signum)
{
	g_response = signum;
}

static void	ft_info(void)
{
	write(1, INFO "[INFO]" TERM_WHITE " usage: " OK "./client" TERM_CYAN
		" [SERVER_PID] [MESSAGE]" RESET "\n", 0x4e);
}
