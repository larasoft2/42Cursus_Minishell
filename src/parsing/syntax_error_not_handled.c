/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_not_handled.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:08:36 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/22 18:47:42 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_handled_double_special_character_and(char *input, char *open_quote)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!(*open_quote))
				*open_quote = input[i];
			else if (*open_quote == input[i])
				*open_quote = '\0';
		}
		else if (!(*open_quote) && input[i] == '&' && input[i + 1] == '&')
		{
			print_error_not_handled_word("&&");
			return (NOT_HANDLED_CHARACTER);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	not_handled_double_pipe(char *input, char *open_quote)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!(*open_quote))
				*open_quote = input[i];
			else if (*open_quote == input[i])
				*open_quote = '\0';
		}
		else if (!(*open_quote) && input[i] == '|' && input[i + 1] == '|')
		{
			print_error_not_handled_word("||");
			return (NOT_HANDLED_CHARACTER);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	not_handled_other_character(char *input, char *open_quote)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!(*open_quote))
				*open_quote = input[i];
			else if (*open_quote == input[i])
				*open_quote = '\0';
		}
		else if (!(*open_quote) && (input[i] == ';' || input[i] == '&'
			|| input[i] == '\\' || input[i] == '*'
			|| input[i] == '(' || input[i] == ')'))
		{
			print_error_not_handled(input[i]);
			return (NOT_HANDLED_CHARACTER);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	not_handled_char_input(char *input, char *open_quote)
{
	if (not_handled_double_pipe(input, open_quote) == NOT_HANDLED_CHARACTER
		|| not_handled_double_special_character_and(input, open_quote) == NOT_HANDLED_CHARACTER
		|| not_handled_other_character(input, open_quote) == NOT_HANDLED_CHARACTER)
		return (NOT_HANDLED_CHARACTER);
	if (number_redir_right(input, open_quote) == WRONG_NUMBER_REDIR
		|| number_redir_left(input, open_quote) == WRONG_NUMBER_REDIR)
		return (NOT_HANDLED_CHARACTER);
	return (EXIT_SUCCESS);
}
