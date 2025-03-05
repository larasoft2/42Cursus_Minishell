/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_redir2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 15:14:00 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void	skip_redirections(t_exec **current)
{
	while ((*current && (*current)->type == TOKEN_REDIR_IN)
		|| (*current && (*current)->type == TOKEN_REDIR_OUT)
		|| (*current && (*current)->type == TOKEN_REDIR_APPEND)
		|| (*current && (*current)->type == TOKEN_REDIR_HEREDOC))
		*current = (*current)->next;
}

int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	return (pipefd[0]);
}

void	handle_empty_pipe(t_ex_ctx *ex_ctx)
{
	int	prev_fd;

	prev_fd = setup_pipe(ex_ctx->pipefd);
	close(ex_ctx->pipefd[1]);
	ex_ctx->current = ex_ctx->current->next;
	ex_ctx->block_begin = ex_ctx->current;
	ex_ctx->fd_in = prev_fd;
}

void	setup_io_for_command(t_ex_ctx *ex_ctx)
{
	if (ex_ctx->fd_in != -1)
	{
		dup2(ex_ctx->fd_in, STDIN_FILENO);
		close(ex_ctx->fd_in);
		ex_ctx->fd_in = -1;
	}
	if (has_pipe(ex_ctx->current) != -1)
		ex_ctx->fd_in = setup_pipe(ex_ctx->pipefd);
	else
	{
		ex_ctx->pipefd[0] = -1;
		ex_ctx->pipefd[1] = -1;
	}
	if (ex_ctx->pipefd[1] != -1)
	{
		dup2(ex_ctx->pipefd[1], STDOUT_FILENO);
		close(ex_ctx->pipefd[1]);
		ex_ctx->pipefd[1] = -1;
	}
	if (ex_ctx->pipefd[0] != -1) //added 04.03
	{
		dup2(ex_ctx->pipefd[0], STDIN_FILENO); //not sure about this dup2
		close(ex_ctx->pipefd[0]);
		ex_ctx->pipefd[0] = -1;
	}
}
