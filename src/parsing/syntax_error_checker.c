/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:24:43 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/05 16:40:25 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_checker(char *input)
{
	if (check_first_character_is_special_without_error(input)
		== FIRST_CHARACTER_IS_SPECIAL)
		return (EXIT_FAILURE);
	if (check_if_unclosed_quotes(input) == UNCLOSED_QUOTES)
		return (EXIT_FAILURE);
	if (input_ends_with_redir(input) == STARTS_OR_ENDS_WITH_PIPE_REDIR)
		return (EXIT_FAILURE);
	if (check_if_not_handled_char_outside_quotes(input)
		== NOT_HANDLED_CHARACTER)
		return (EXIT_FAILURE);
	if (input_starts_or_ends_with_pipe(input)
		== STARTS_OR_ENDS_WITH_PIPE_REDIR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	syntax_error_checker_spaces_empty(char *input)
{
	if (check_empty_input(input) == EMPTY_STRING)
		return (EXIT_FAILURE);
	if (check_only_whitespace_intput(input) == INPUT_ONLY_WHITESPACE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
