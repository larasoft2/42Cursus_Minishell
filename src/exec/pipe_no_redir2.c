/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_no_redir2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:13:35 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 15:13:25 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ex_ctx(t_ex_ctx *ex_ctx, t_exec *ex)
{
	ex_ctx->ex = ex;
	ex_ctx->fd_in = STDIN_FILENO;
	ex_ctx->begin = ex;
}

void	prepare_pipe(int *pipefd, t_exec *ex)
{
	if (ex->next && ex->next->type == TOKEN_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
	}
}

void	handle_child_io(int fd_in, int *pipefd)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
	if (pipefd[1] != -1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		ft_close_fds(pipefd[1]);
	}
	if (pipefd[0] != -1)
		ft_close_fds(pipefd[0]);
}

void	handle_parent_io(int *fd_in, int *pipefd)
{
	if (*fd_in != STDIN_FILENO)
	{
		ft_close_fds(*fd_in);
		*fd_in = -1;
	}
	if (pipefd[1] != -1)
	{
		ft_close_fds(pipefd[1]);
		pipefd[1] = -1;
	}
	*fd_in = pipefd[0];
}
