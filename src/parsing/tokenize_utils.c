/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:59:07 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/15 17:58:44 by racoutte         ###   ########.fr       */
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

void	skip_spaces(char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
}

void	print_tokens(t_token_node *list)
{
	while (list)
	{
		printf("Type: %d, Value: %s\n", list->type, list->value);
		list = list->next;
	}
}
