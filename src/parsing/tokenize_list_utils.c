/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:08 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 15:52:41 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_node	*create_token_node(t_token_type type, char *value)
{
	t_token_node	*new_token;

	new_token = (t_token_node *)malloc(sizeof(t_token_node));
	if (!new_token)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (NULL);
	}
	if (!value)
	{
		ft_putstr_fd("Error: NULL value passed to create_token_node\n",
			STDERR_FILENO);
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		ft_putstr_fd("Error: malloc strdup failed\n", STDERR_FILENO);
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token_node **list, t_token_node *new_token)
{
	t_token_node	*temp;

	if (!(*list))
	{
		*list = new_token;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	if (!new_token)
	{
		ft_putstr_fd("Error: Attempting to add NULL token\n", STDERR_FILENO);
		return ;
	}
}
