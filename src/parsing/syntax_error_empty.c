/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:15:08 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/05 11:32:35 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_input(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (NOT_EMPTY_STRING);
		i++;
	}
	return (EMPTY_STRING);
}

int	check_only_whitespace_intput(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (EXIT_SUCCESS);
		i++;
	}
	return (INPUT_ONLY_WHITESPACE);
}

int	check_first_character_is_special_without_error(char *input)
{
	if (input[0] == ':' || input[0] == '!')
		return (FIRST_CHARACTER_IS_SPECIAL);
	else
		return (EXIT_SUCCESS);
}
