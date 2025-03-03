/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_redir2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/03 15:57:14 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_command_in_block(t_exec *begin, t_exec *end)
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
		perror("pipe failed"); //check free
		exit(EXIT_FAILURE);
	}
	return (pipefd[0]);
}

void	handle_empty_pipe(t_pipes *p)
{
	int	prev_fd;

	prev_fd = setup_pipe(p->pipefd);
	close(p->pipefd[1]);
	p->current = p->current->next;
	p->block_begin = p->current;
	p->fd_in = prev_fd;
}

void	setup_io_for_command(t_pipes *p)
{
	if (p->fd_in != -1)
	{
		dup2(p->fd_in, STDIN_FILENO);
		close(p->fd_in);
		p->fd_in = -1;
	}
	if (has_pipe(p->current) != -1)
		p->fd_in = setup_pipe(p->pipefd);
	else
	{
		p->pipefd[0] = -1;
		p->pipefd[1] = -1;
	}
	if (p->pipefd[1] != -1)
	{
		dup2(p->pipefd[1], STDOUT_FILENO);
		close(p->pipefd[1]);
		p->pipefd[1] = -1;
	}
}
