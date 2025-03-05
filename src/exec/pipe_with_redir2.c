/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_redir2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 20:45:59 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe_redir(int pipefd[2])
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

	prev_fd = setup_pipe_redir(ex_ctx->pipefd);
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
		ex_ctx->fd_in = setup_pipe_redir(ex_ctx->pipefd);
	else
	{
		ex_ctx->pipefd[0] = -1;
		ex_ctx->pipefd[1] = -1;
	}
	if (ex_ctx->pipefd[1] != -1)
	{
		close(ex_ctx->pipefd[1]);
		ex_ctx->pipefd[1] = -1;
	}
}
