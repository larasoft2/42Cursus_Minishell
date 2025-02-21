/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:40:57 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 23:51:22 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*get_next_exec_token(t_exec *ex)
{
	ex = ex->next;
	if (ex && ex->type == TOKEN_PIPE)
		ex = ex->next;
	return (ex);
}

t_exec	*find_next_valid_token(t_exec *ex)
{
	while (ex && (ex->type > 1))
		ex = ex->next;
	return (ex);
}

void	restore_fds(int *std_dup)
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

void	ft_close_fd(int *pipefd)
{
	if (pipefd[0] != -1)
	{
		close(pipefd[0]);
		pipefd[0] = -1;
	}
	if (pipefd[1] != -1)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
}

void	ft_close_fds(int fd)
{
	if (fd > 2)
		close(fd);
}
