/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:06:44 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/11 18:30:33 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
int	is_quote(char c)
{
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '\'')
		return (SINGLE_QUOTE);
	return (EXIT_SUCCESS);
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '\'')
		return (SINGLE_QUOTE);
	return (EXIT_SUCCESS);
}

int	check_if_unclosed_quotes(char *input)
int	check_if_unclosed_quotes(char *input)
{
	size_t	i;
	char	open_quote;
	char	open_quote;

	i = 0;
	open_quote = '\0';
	open_quote = '\0';
	while (input[i])
	{
		if (is_quote(input[i]) && !open_quote)
			open_quote = input[i];
		else if (input[i] == open_quote)
			open_quote = '\0';
		if (is_quote(input[i]) && !open_quote)
			open_quote = input[i];
		else if (input[i] == open_quote)
			open_quote = '\0';
		i++;
	}
	if (open_quote != '\0')
	if (open_quote != '\0')
	{
		print_error_syntax_message(SYNTAX_ERROR_UNCLOSED_QUOTES);
		return (UNCLOSED_QUOTES);
	}
	return (CLOSED_QUOTES);
}

int	check_if_not_handled_char_outside_quotes(char *input)
{
	size_t	i;
	char	open_quote;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!open_quote)
				open_quote = input[i];
			else if (input[i] == open_quote)
				open_quote = '\0';
		}
		else if (!open_quote && not_handled_char_input(&input[i], &open_quote))
			return (NOT_HANDLED_CHARACTER);
		i++;
	}
	return (EXIT_SUCCESS);
}
