/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:48:29 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/03 20:12:12 by lusavign         ###   ########.fr       */
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
    dup2(std_dup[1], STDOUT_FILENO);
	dup2(std_dup[0], STDIN_FILENO);
	close(std_dup[0]);
	close(std_dup[1]);
}

int	is_pipe(t_exec *ex)
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