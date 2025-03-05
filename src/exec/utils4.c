/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:47:46 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 14:57:53 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_code(int status)
{
	modify_value_exit_code(status / 256);
	if (g_signal != 0)
		modify_value_exit_code(g_signal);
}

int	starting_hd(t_exec *ex, int *std_dup)
{
	if (has_heredoc(ex) == 1 && g_signal != SIGINT)
		ft_open_heredocs(ex, ex->fd_in);
	if (g_signal == SIGINT)
	{
		modify_value_exit_code(130);
		dup2(std_dup[0], STDIN_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	skip_redirections(t_exec **current)
{
	while ((*current && (*current)->type == TOKEN_REDIR_IN)
		|| (*current && (*current)->type == TOKEN_REDIR_OUT)
		|| (*current && (*current)->type == TOKEN_REDIR_APPEND)
		|| (*current && (*current)->type == TOKEN_REDIR_HEREDOC))
		*current = (*current)->next;
}

bool	check_cmd_in_block(t_exec *begin, t_exec *end)
{
	t_exec	*temp;

	temp = begin;
	while (temp && temp != end)
	{
		if (temp->type == TOKEN_WORD)
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	init_ex_ctx(t_ex_ctx *ex_ctx, t_exec *ex)
{
	ex_ctx->ex = ex;
	ex_ctx->fd_in = STDIN_FILENO;
	ex_ctx->begin = ex;
}
