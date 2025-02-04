/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:57:13 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/03 19:01:00 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_word_node(char *input, int *i, t_token_node **token_list)
{
	t_token_type	type;
	char			*word;

	type = TOKEN_WORD;
	word = read_word(input, i);
	add_token(token_list, create_token_node(type, word));
	free(word);
}

char	*read_word(char *input, int *i)
{
	char	open_quote;
	char	*word;
	int		start_index;

	open_quote = '\0';
	start_index = *i;
	while (input[*i])
	{
		if (is_quote(input[*i]) && !open_quote)
			open_quote = input[*i];
		else if (input[*i] == open_quote)
			open_quote = '\0';
		if ((open_quote != '\0')
			|| (!is_pipe_redirin_redirout_character(input[*i])
				&& !ft_isspace(input[*i])))
			(*i)++;
		else
			break ;
	}
	word = ft_substr(input, start_index, *i - start_index);
	if (!word)
		return (ft_putstr_fd("Error: Mem alloc failed\n", STDERR_FILENO), NULL);
	return (word);
}
