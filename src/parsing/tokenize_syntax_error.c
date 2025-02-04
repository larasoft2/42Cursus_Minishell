/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_syntax_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:31:55 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/29 21:43:35 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_token(t_token_node *token_list)
{
	if (token_list->type == TOKEN_PIPE)
		print_error_syntax_message(SYNTAX_ERROR_PIPE_SINGLE);
	else if (token_list->type == TOKEN_REDIR_IN
		|| token_list->type == TOKEN_REDIR_HEREDOC)
		print_error_syntax_message(SYNTAX_ERROR_REDIR_SINGLE_LEFT);
	else if (token_list->type == TOKEN_REDIR_OUT
		|| token_list->type == TOKEN_REDIR_APPEND)
		print_error_syntax_message(SYNTAX_ERROR_REDIR_SINGLE_RIGHT);
}

int	check_error_token_pipe(t_token_node *token_list)
{
	t_token_node	*tmp;
	int				previous_is_pipe;

	if (!token_list)
		return (EXIT_FAILURE);
	tmp = token_list;
	while (tmp->next != NULL)
	{
		if (tmp->value && ft_strncmp(tmp->value, "|", 1) == 0)
		{
			if (previous_is_pipe == PIPE)
			{
				print_error_token(tmp);
				return (EXIT_FAILURE);
			}
			previous_is_pipe = PIPE;
		}
		else
			previous_is_pipe = 0;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	check_error_token_redir(t_token_node *token_list)
{
	t_token_node	*tmp;

	if (!token_list)
		return (EXIT_FAILURE);
	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_REDIR_APPEND
			|| tmp->type == TOKEN_REDIR_HEREDOC)
		{
			if (tmp->value == NULL || tmp->value[0] == '\0')
			{
				print_error_token(tmp);
				return (EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	check_error_token(t_token_node *token_list)
{
	if (check_error_token_redir(token_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_error_token_pipe(token_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
