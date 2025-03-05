/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_for_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:33:46 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 19:32:08 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(t_exec *ex, int *fd_in)
{
	if (ex->type == TOKEN_REDIR_OUT || ex->type == TOKEN_REDIR_APPEND)
	{
		if (ex->type == TOKEN_REDIR_OUT)
			ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (ex->type == TOKEN_REDIR_APPEND)
			ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (ex->fd_out < 0)
		{
			if (*fd_in > 0)
				close(*fd_in);
			return (modify_value_exit_code(1), print_error(ex->arg[0]));
		}
		dup2(ex->fd_out, STDOUT_FILENO);
		if (ex->fd_out != -1)
		{
			ft_close_fds(ex->fd_out);
			ex->fd_out = -1;
		}
	}
	return (EXIT_SUCCESS);
}

int	redir_in(t_exec *ex, int *fd_in)
{
	if (ex->type == TOKEN_REDIR_IN)
	{
		if (*fd_in > 2)
			ft_close_fds(*fd_in);
		*fd_in = open(ex->arg[0], O_RDONLY);
		if (*fd_in < 0)
			return (modify_value_exit_code(1), print_error(ex->arg[0]));
	}
	else if (ex->type == TOKEN_REDIR_HEREDOC && g_signal != SIGINT)
	{
		if (*fd_in > 2)
			ft_close_fds(*fd_in);
		*fd_in = open(ex->hd_name, O_RDONLY);
		if (*fd_in < 0)
			return (modify_value_exit_code(1), print_error(ex->hd_name));
	}
	return (EXIT_SUCCESS);
}

int	ft_open(t_exec *ex, int *fd_in)
{
	if (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_HEREDOC)
	{
		if (redir_in(ex, fd_in) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (ex->type == TOKEN_REDIR_OUT || ex->type == TOKEN_REDIR_APPEND)
	{
		if (redir_out(ex, fd_in) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	handle_redir(t_exec *ex)
{
	t_exec	*current;
	int		fd_in;

	fd_in = 0;
	current = ex;
	while (current)
	{
		if (current->type > 1)
		{
			if (ft_open(current, &fd_in) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	if (fd_in > 2)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
	return (EXIT_SUCCESS);
}

int	handle_redir_in_pipe(t_exec *ex, int pipefd)
{
	int		fd_in;
	t_exec	*current;

	fd_in = pipefd;
	current = ex;
	while (current)
	{
		if (current->type > 1)
		{
			if (ft_open(current, &fd_in) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (current->type == TOKEN_PIPE)
			break ;
		else
			current = current->next;
	}
	if (fd_in > 2)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
	return (EXIT_SUCCESS);
}
