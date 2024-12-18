/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:57:13 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/18 17:20:49 by racoutte         ###   ########.fr       */
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
		if (is_quote(input[*i]) && !open_quote) // si le caractere est une quote, on le stocke
			open_quote = input[*i];
		else if (input[*i] == open_quote) // si on rencontre la meme quote pour la 2eme fois, on remet open_quote a 0
			open_quote = '\0';
		if ((open_quote != '\0') || (!is_pipe_redirin_redirout_character(input[*i]) && !ft_isspace(input[*i]))) // si on est plus dans une quote et qu'on tombe sur un espace/pipe/redir_in/redir_out, on quitte la boucle
			(*i)++;
		else
			break ;
	}
	word = ft_substr(input, start_index, *i - start_index); // on stocke le mot depuis le start_index (stocke avant d'avoir avance dans la boucle) jusqu'au current index
	if (!word)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return (NULL);
	}
	return (word);
}
