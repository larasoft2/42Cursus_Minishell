/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:48:29 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/19 16:56:26 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_exec *ex, int *std_dup)
{
    ex->fd_in = STDIN_FILENO;
    ex->fd_out = STDOUT_FILENO;
    std_dup[0] = dup(STDIN_FILENO);
    std_dup[1] = dup(STDOUT_FILENO);
}

void    restore_fds(int *std_dup)
{
	dup2(std_dup[0], STDIN_FILENO);
	if (std_dup[0] != -1)
	{
		close(std_dup[0]);
		std_dup[0] = -1;
	}
    dup2(std_dup[1], STDOUT_FILENO);
	if (std_dup[1] != -1)
	{
		close(std_dup[1]);
		std_dup[1] = -1;
	}
}

int	has_heredoc(t_exec *ex)
{
	int	i;

	if (!ex)
		return (0);
	i = 0;
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
	int	i;

	if (!ex)
		return (0);
	i = 0;
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
	int	i;

	if (!ex)
		return (0);
	i = 0;
	while (ex)
	{
		if (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_OUT 
			|| ex->type == TOKEN_REDIR_APPEND || ex->type == TOKEN_REDIR_HEREDOC)
			return (1);
		ex = ex->next;
	}
	return (-1);
}
