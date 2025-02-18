/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:15:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 16:04:43 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_special_node(char *input, int *i, t_token_node **token_list)
{
	if (input[*i] == '|')
		create_pipe_node(i, token_list);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		create_redir_in_node(input, i, token_list);
	else if (input[*i] == '>' && input[*i + 1] != '>')
		create_redir_out_node(input, i, token_list);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		create_redir_append_node(input, i, token_list);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		create_heredoc_node(input, i, token_list);
}

t_token_node	*tokenize_input(char *input)
{
	t_token_node	*token_list;
	int				i;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (input[i] == '\0')
			break ;
		if (is_pipe_redirin_redirout_character(input[i]))
			create_special_node(input, &i, &token_list);
		else if (!is_pipe_redirin_redirout_character(input[i]))
			create_word_node(input, &i, &token_list);
		if (check_error_token(token_list) == EXIT_FAILURE)
		{
			free_token_list(&token_list);
			return (NULL);
		}
	}
	return (token_list);
}
