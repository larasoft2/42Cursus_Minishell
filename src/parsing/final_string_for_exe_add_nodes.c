/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_string_for_exe_add_nodes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:40:04 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/14 12:52:27 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*add_exec_node_with_type(t_exec **exec_list, t_token_type type,
	char *value)
{
	t_exec	*new_node;
	t_exec	*temp;

	temp = *exec_list;
	new_node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!new_node)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (NULL);
	}
	init_exec_node(new_node, type, value);
	if (!new_node->arg)
	{
		free(new_node);
		return (NULL);
	}
	if (*exec_list == NULL)
		*exec_list = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

void	add_word(char **arg, char *value, int i)
{
	if (i >= MAX_ARGS - 1)
	{
		ft_putstr_fd("Error: too many arguments\n", STDERR_FILENO);
		return ;
	}
	arg[i] = ft_strdup(value);
	if (!arg[i])
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return ;
	}
	arg[i + 1] = NULL;
}

t_exec	*add_word_to_exec_word_node(t_exec **exec_list, char *value,
	int *word_count, t_exec **last_exec_node)
{
	t_exec	*temp;

	temp = *exec_list;
	if (*exec_list == NULL || *word_count == 0)
	{
		add_exec_node_with_type(exec_list, TOKEN_WORD, value);
		*last_exec_node = *exec_list;
		while ((*last_exec_node)->next)
			*last_exec_node = (*last_exec_node)->next;
		*word_count = 1;
		return (*exec_list);
	}
	if (*last_exec_node && (*last_exec_node)->type == TOKEN_WORD
		&& *word_count > 0)
	{
		add_word((*last_exec_node)->arg, value, *word_count);
		(*word_count)++;
	}
	return (*exec_list);
}
