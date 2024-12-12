/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:15:09 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/12 15:39:56 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_special_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*value;

	if (input[*i] == '|')
		create_pipe_node(input, i, token_list);
	else if (input[*i] == '<' && input[*i + 1] != '<')
		create_redir_in_node(input, i, token_list);
	else if (input[*i] == '>' && input[*i + 1] != '>')
		create_redir_out_node(input, i, token_list);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		create_redir_append_node(input, i, token_list);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		create_heredoc_node(input, i, token_list);
	add_token(token_list, create_token_node(type, value));
	*i += ft_strlen(value);
}

void	create_word_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*word;

	type = TOKEN_WORD;
	word = ft_strdup("");
	while (!is_pipe_redirin_redirout_character(input[*i]) && input[*i])
	{
		word = ft_strjoin(word, input[*i]);
		*i++;
	}
	add_token(token_list, create_token_node(type, word));
}

t_token_node	*tokenize_input(char *input)
{
	t_token_node	**token_list;
	int				i;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (is_pipe_redirin_redirout_character(input[i]))
			create_special_node(input, &i, token_list);
		else if (!is_pipe_redirin_redirout_character(input[i]))
			create_word_node(input, &i, &token_list);
		i++;
	}
	return (token_list);
}