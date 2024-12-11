/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:43:40 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/11 18:02:22 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message_redir_right(int count)
{
	if (count == 3)
	{
		print_error_syntax_message(SYNTAX_ERROR_REDIR_SINGLE_RIGHT);
		return (WRONG_NUMBER_REDIR);
	}
	else if (count > 3)
	{
		print_error_syntax_message(SYNTAX_ERROR_REDIR_DOUBLE_RIGHT);
		return (WRONG_NUMBER_REDIR);
	}
	return (EXIT_SUCCESS);
}

int	error_message_redir_left(int count)
{
	if (count == 3)
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (WRONG_NUMBER_REDIR);
	}
	else if (count == 4)
	{
		print_error_syntax_message(SYNTAX_ERROR_REDIR_SINGLE_LEFT);
		return (WRONG_NUMBER_REDIR);
	}
	else if (count > 4)
	{
		print_error_syntax_message(SYNTAX_ERROR_REDIR_DOUBLE_LEFT);
		return (WRONG_NUMBER_REDIR);
	}
	return (EXIT_SUCCESS);
}

int	input_ends_with_redir(char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (input[len - 1] == '<' || input[len - 1] == '>')
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
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
		else if (!(*open_quote) && input[i] == '>')
		{
			while (input[i] == '>')
			{
				count++;
				if (input[i + 1] != '>' && error_message_redir_right(count) == WRONG_NUMBER_REDIR)
					return (WRONG_NUMBER_REDIR);
				i++;
			}
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
		else if (!(*open_quote) && input[i] == '<')
		{
			while (input[i] == '<')
			{
				count++;
				if (input[i + 1] != '<' && error_message_redir_left(count) == WRONG_NUMBER_REDIR)
					return (WRONG_NUMBER_REDIR);
				i++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
