/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:40:57 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 17:43:30 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
