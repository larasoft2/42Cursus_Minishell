/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:08 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/12 15:23:34 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_redirin_redirout_character(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	return (EXIT_SUCCESS);
}

t_token_node	*create_token_node(t_token_type type, char *value)
{
	t_token_node	*new_token;

	new_token = (t_token_node *)malloc(sizeof(t_token_node));
	if (!new_token)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
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
}

void	print_tokens(t_token_node *list)
{
	while (list)
	{
		ft_printf("Type: %d, Value: '%s'\n", list->type, list->value);
		list = list->next;
	}
}