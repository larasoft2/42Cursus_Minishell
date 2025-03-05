/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:26:46 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/05 15:16:03 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_signal(void)
{
	return (0);
}

void	sigint_heredoc(int sig)
{
	g_signal = sig;
	modify_value_exit_code(128 + SIGINT);
	rl_replace_line("", 0);
	rl_done = 1;
}

void	setup_heredoc_signals_handling(void)
{
	g_signal = 0;
	rl_event_hook = ft_check_signal;
	signal(SIGINT, sigint_heredoc);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}
