/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:48:29 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 13:17:39 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_dup(t_exec *ex, int *std_dup)
{
	ex->fd_in = STDIN_FILENO;
	ex->fd_out = STDOUT_FILENO;
	std_dup[0] = dup(STDIN_FILENO);
	std_dup[1] = dup(STDOUT_FILENO);
}

int	has_heredoc(t_exec *ex)
{
	if (!ex)
		return (0);
	while (ex)
	{
		if (ex->type == TOKEN_REDIR_HEREDOC)
			return (1);
		ex = ex->next;
	}
	return (-1);
}

int	has_pipe(t_exec *ex)
{
	if (!ex)
		return (0);
	while (ex)
	{
		if (ex->type == TOKEN_PIPE)
			return (1);
		ex = ex->next;
	}
	return (-1);
}

int	has_redir(t_exec *ex)
{
	if (!ex)
		return (0);
	while (ex)
	{
		if (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_OUT
			|| ex->type == TOKEN_REDIR_APPEND
			|| ex->type == TOKEN_REDIR_HEREDOC)
			return (1);
		ex = ex->next;
	}
	return (-1);
}

void	init_ex_ctx_for_redir(t_ex_ctx *ex_ctx, t_exec *ex, int *std_dup)
{
	ex_ctx->fd_in = -1;
	ex_ctx->current = ex;
	ex_ctx->block_begin = ex;
	ex_ctx->begin = ex;
	ex_ctx->std_dup[0] = std_dup[0];
	ex_ctx->std_dup[1] = std_dup[1];
}
