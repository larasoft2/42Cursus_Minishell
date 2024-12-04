/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:15:08 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/04 15:10:50 by racoutte         ###   ########.fr       */
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
