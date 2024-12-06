/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:07:51 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/06 13:19:56 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_starts_or_ends_with_pipe(char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (input[0] == '|')
	{
		print_error_syntax_message(SYNTAX_ERROR_PIPE_SINGLE);
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	}
	// if (input[0] == '-')
	// {
	// 	print_error_not_handled('-');
	// 	return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	// }
	if (input[len - 1] == '|')
	{
		print_error_not_handled('|');
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	}
	return (EXIT_SUCCESS);
}



