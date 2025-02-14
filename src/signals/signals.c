/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:33:15 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:38 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_signal(void)
{
	return (0);
}

static void	sigint_prompt(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_exec(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	write(STDOUT_FILENO, "\n", 1);
}

static void	sigint_heredoc(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	//appeler une fonction qui detruit le heredoc.. destroy_heredoc()
	rl_event_hook = ft_check_signal;
	rl_done = 1; // termine readline
}

static void	sigquit_exec(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGQUIT);
	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
}

void	handle_signals(bool exec, bool heredoc)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (exec)
	{
		sa.sa_handler = sigint_exec;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = sigquit_exec;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (heredoc)
	{
		sa.sa_handler = sigint_heredoc;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = sigint_prompt;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}
