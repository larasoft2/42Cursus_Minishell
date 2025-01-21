/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:59:07 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/20 17:03:03 by racoutte         ###   ########.fr       */
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

void	print_tokens_exec_list(t_exec *exec_list)
{
	t_exec *current;
	int	i;

	current = exec_list;
	while (current)
	{
		i = 0;
		printf("Command type: %d\n", current->type);
		if (current->arg)
		{
			while (current->arg[i])
			{
				printf("Arg[%d]: %s\n", i, current->arg[i]);
				i++;
			}
		}
		current = current->next;
	}
}
