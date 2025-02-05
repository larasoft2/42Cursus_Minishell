/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:25:00 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/05 14:21:21 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_node **list)
{
	t_token_node *temp;

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
	t_env *temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	*list = NULL;
}

void	free_exec_list(t_exec **list)
{
	t_exec *temp;
	int i;

	if (!list || !*list)
		return;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->arg)
		{
			i = 0;
			while (temp->arg[i])
			{
				free(temp->arg[i]);
				i++;
			}
			free(temp->arg);
		}
		free(temp);
	}
	*list = NULL;
}

void	free_routine_all_lists(t_token_node **tokens, t_env **env,
	t_exec **exec)
{
	free_token_list(tokens);
	free_env_list(env);
	free_exec_list(exec);
}
