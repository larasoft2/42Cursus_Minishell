/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_redir_print_msg.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:07:57 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/27 17:59:11 by racoutte         ###   ########.fr       */
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

int	check_next_char_for_redir(char *input, size_t i)
{
	if (input[i + 1] == '\0')
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (WRONG_NUMBER_REDIR);
	}
	return (EXIT_SUCCESS);
}
