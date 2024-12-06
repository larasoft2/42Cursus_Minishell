/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:06:44 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/06 12:06:31 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_quote(char c)
{
	if (c == '"')
		return (DOUBLE_QUOTE);
	return (EXIT_SUCCESS);
}

int	is_single_quote(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	return (EXIT_SUCCESS);
}

int	check_if_unclosed_quotes(char *input)
{
	size_t	i;
	char	open_quote;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (open_quote == '\0')
		{
			if (is_double_quote(input[i]) == DOUBLE_QUOTE)
				open_quote = '"';
			else if (is_single_quote(input[i]) == SINGLE_QUOTE)
				open_quote = '\'';
		}
		else if (input[i] == open_quote)
			open_quote = '\0';
		i++;
	}
	if (open_quote != '\0')
	{
		print_error_syntax_message(SYNTAX_ERROR_UNCLOSED_QUOTES);
		return (UNCLOSED_QUOTES);
	}
	return (CLOSED_QUOTES);
}
