/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:33:15 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 16:36:52 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_signal(void)
{
	return (0);
}

void	destroy_heredoc(char *heredoc)
{
	if (heredoc)
		unlink(heredoc);
}

static void	sigint_prompt(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_heredoc(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	write(STDOUT_FILENO, "\n", 1);
	rl_event_hook = ft_check_signal;
	rl_done = 1;
}

// static void	sigint_exec(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGINT);
// 	write(STDOUT_FILENO, "\n", 1);
// }

// static void	sigquit_exec(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGQUIT);
// 	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
// }

static void    sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
}

void    setup_command_mode_signals_handling(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGCONT, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
}

void	setup_main_prompt_signals_handling(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	setup_default_signals_handling(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	setup_heredoc_signals_handling(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

// static int	ft_check_signal(void)
// {
// 	return (0);
// }

// static void	sigint_prompt(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGINT);
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// static void	sigint_exec(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGINT);
// 	write(STDOUT_FILENO, "\n", 1);
// }

// static void	sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGINT);
// 	//appeler une fonction qui detruit le heredoc.. destroy_heredoc()
// 	rl_event_hook = ft_check_signal;
// 	rl_done = 1; // termine readline
// }

// static void	sigquit_exec(int sig)
// {
// 	(void)sig;
// 	modify_value_exit_code(128 + SIGQUIT);
// 	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
// }

// void	handle_signals(bool exec, bool heredoc)
// {
// 	struct sigaction sa;

// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	if (exec)
// 	{
// 		sa.sa_handler = sigint_exec;
// 		sigaction(SIGINT, &sa, NULL);
// 		sa.sa_handler = sigquit_exec;
// 		sigaction(SIGQUIT, &sa, NULL);
// 	}
// 	else if (heredoc)
// 	{
// 		sa.sa_handler = sigint_heredoc;
// 		sigaction(SIGINT, &sa, NULL);
// 		sa.sa_handler = SIG_IGN;
// 		sigaction(SIGQUIT, &sa, NULL);
// 	}
// 	else
// 	{
// 		sa.sa_handler = sigint_prompt;
// 		sigaction(SIGINT, &sa, NULL);
// 		sa.sa_handler = SIG_IGN;
// 		sigaction(SIGQUIT, &sa, NULL);
// 	}
// }
