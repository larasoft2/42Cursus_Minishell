/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_string_for_exe_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:50:01 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/03 16:51:43 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_node(t_exec *new_node, t_token_type type, char *value)
{
	new_node->type = type;
	new_node->arg = (char **)ft_calloc(MAX_ARGS, sizeof(char *));
	if (!new_node->arg)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		free(new_node);
		return ;
	}
	new_node->arg[0] = ft_strdup(value);
	if (!new_node->arg[0])
	{
		ft_putstr_fd("Error: strdup failed\n", STDERR_FILENO);
		free(new_node->arg);
		free(new_node);
		return ;
	}
	new_node->fd_in = 0;
	new_node->fd_out = 0;
	// new_node->pid = NULL;
	new_node->hd_name = NULL;
	new_node->next = NULL;
}
