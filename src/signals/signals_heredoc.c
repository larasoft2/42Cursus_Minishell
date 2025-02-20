/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:26:46 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/20 13:03:15 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_exec	**get_current_exec(void)
// {
// 	static t_exec	*current_exec = NULL;

// 	return (&current_exec);
// }

static int	ft_check_signal(void)
{
	return (0);
}

// void	destroy_heredoc(char *heredoc)
// {
// 	if (heredoc)
// 		unlink(heredoc);
// }

void	sigint_heredoc(int sig)
{
	g_signal = sig;
	modify_value_exit_code(128 + SIGINT);
	// t_exec *ex = *get_current_exec();
	// if (ex)
	// {
	// 	if (ex->hd_name)
	// 	{
	// 		unlink(ex->hd_name);
	// 		free(ex->hd_name);
	// 		ex->hd_name = NULL;
	// 	}
	// }
	//write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

void	setup_heredoc_signals_handling(void)
{
	g_signal = 0;
	//*get_current_exec() = ex;
	rl_event_hook = ft_check_signal;
	signal(SIGINT, sigint_heredoc);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
