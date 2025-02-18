/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:26:46 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 18:28:03 by racoutte         ###   ########.fr       */
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

void	sigint_heredoc(int sig)
{
	(void)sig;
	modify_value_exit_code(128 + SIGINT);
	//destroy_heredoc?
	write(STDOUT_FILENO, "\n", 1);
	rl_event_hook = ft_check_signal;
	rl_done = 1;
}
