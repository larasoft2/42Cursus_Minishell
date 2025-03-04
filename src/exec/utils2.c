/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:48:29 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 00:21:08 by lusavign         ###   ########.fr       */
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

void	print_delimiter_error_message(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	if (delimiter != NULL)
		ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
