/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_not_handled.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:08:36 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/04 16:21:05 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_handled_double_pipe(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			ft_printf("minishell: syntax error, not handled character `||'\n");
			return (NOT_HANDLED_CHARACTER);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	not_handled_other_character(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' || input[i] == '&' || input[i] == '/')
		{
			ft_printf("minishell: syntax error, not handled character `%c'\n", input[i]);
			return (NOT_HANDLED_CHARACTER);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	not_handled_char_input(char *input)
{
	if (not_handled_double_pipe(input) == NOT_HANDLED_CHARACTER
		|| not_handled_other_character(input) == NOT_HANDLED_CHARACTER)
		return (NOT_HANDLED_CHARACTER);
	return (EXIT_SUCCESS);
}