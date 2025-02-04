/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_redir_print_msg.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:07:57 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/28 16:29:05 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message_redir_right(int count)
{
	if (count == 2)
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (WRONG_NUMBER_REDIR);
	}
	if (count == 1 || count == 3)
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
	if (count == 2 || count == 3)
	{
		print_error_syntax_message(SYNTAX_ERROR_NEWLINE);
		return (WRONG_NUMBER_REDIR);
	}
	else if (count == 1 || count == 4)
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
