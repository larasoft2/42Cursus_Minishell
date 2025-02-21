/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:18:24 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/21 18:02:09 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	g_signal = 128 + SIGQUIT;
	modify_value_exit_code(128 + SIGQUIT);
	write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
}

void	sigint_prompt(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	modify_value_exit_code(128 + SIGINT);
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	modify_value_exit_code(128 + SIGINT);
	write(STDOUT_FILENO, "\n", 1);
}

void	sigpipe_handler(int sig)
{
	(void)sig;
	g_signal = 0;
}
