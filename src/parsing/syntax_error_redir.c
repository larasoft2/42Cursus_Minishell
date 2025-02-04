/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:43:40 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/29 14:03:32 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_ends_with_redir(char *input)
{
	size_t	len;

	if (!input || *input == '\0')
		return (EXIT_SUCCESS);
	len = ft_strlen(input);
	if (len > 0 && (input[len - 1] == '<' || input[len - 1] == '>'))
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	}
	return (EXIT_SUCCESS);
}

int	count_redir(char symbol, int *count)
{
	if ((symbol == '>'
		&& error_message_redir_right(*count) == WRONG_NUMBER_REDIR)
			|| (symbol == '<'
				&& error_message_redir_left(*count) == WRONG_NUMBER_REDIR))
	{
		return (WRONG_NUMBER_REDIR);
	}
	return (EXIT_SUCCESS);
}

int	handle_redir_symbol(char *input, size_t *i, int *count, char symbol)
{
	*count = 0;
	while (input[*i] == symbol)
	{
		(*count)++;
		if (input[*i + 1] == '\0' || (input[*i + 1] && ft_isspace(input[*i + 1])))
		{
			if (count_redir(symbol, count) == WRONG_NUMBER_REDIR)
				return (WRONG_NUMBER_REDIR);
		}
		else if (input[*i + 1] != symbol)
		{
			if (count_redir(symbol, count) == WRONG_NUMBER_REDIR)
				return (WRONG_NUMBER_REDIR);
		}
		(*i)++;
		if (input[*i] == '\0')
			break ;
	}
	return (EXIT_SUCCESS);
}

int	number_redir_right(char *input, char *open_quote)
{
	size_t	i;
	int		count;

	i = 0;
	while (input[i])
	{
		count = 0;
		if (is_quote(input[i]))
		{
			if (!(*open_quote))
				*open_quote = input[i];
			else if (*open_quote == input[i])
				*open_quote = '\0';
		}
		if (!(*open_quote) && input[i] == '>')
		{
			if (!input[i + 1]
				|| handle_redir_symbol(input, &i, &count, '>')
					== WRONG_NUMBER_REDIR)
				return (WRONG_NUMBER_REDIR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	number_redir_left(char *input, char *open_quote)
{
	size_t	i;
	int		count;

	i = 0;
	while (input[i])
	{
		count = 0;
		if (is_quote(input[i]))
		{
			if (!(*open_quote))
				*open_quote = input[i];
			else if (*open_quote == input[i])
				*open_quote = '\0';
		}
		if (!(*open_quote) && input[i] == '<')
		{
			if (!input[i + 1]
				|| handle_redir_symbol(input, &i, &count, '<')
					== WRONG_NUMBER_REDIR)
				return (WRONG_NUMBER_REDIR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
