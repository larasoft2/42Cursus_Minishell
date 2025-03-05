/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:25:00 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/05 17:45:04 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_token_list(t_token_node **list)
{
	t_token_node	*temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->value);
		free(temp);
	}
	*list = NULL;
}

void	free_env_list(t_env **list)
{
	t_env	*temp;
	t_env	*next;

	if (!list || !*list)
		return ;
	temp = *list;
	while (temp)
	{
		next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = next;
	}
	*list = NULL;
}

void	free_exec_list(t_exec **list)
{
	t_exec	*temp;
	t_exec	*next;

	if (!list || !*list)
		return ;
	temp = *list;
	if (list != NULL)
	{
		while (temp)
		{
			next = temp->next;
			if (temp->arg)
				ft_free_and_null(temp->arg);
			free(temp);
			temp = next;
		}
	}
	*list = NULL;
}

void	free_exec_node(t_exec *node)
{
	if (node->arg)
		ft_free_and_null(node->arg);
	free(node);
}

void	free_for_ft_exec(t_exec *ex, t_env **env, char **env_array, char *path_cmd)
{
	ft_free_and_null(env_array);
	free(path_cmd);
	free_exec_list(&ex);
	free_env_list(env);
}
