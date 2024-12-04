/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:06:44 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/04 17:02:04 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_number_double_quotes(char *input)
{
	size_t	i;
	int		count_double_quotes;

	i = 0;
	count_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '"')
			count_double_quotes++;
		i++;
	}
	return (count_double_quotes);
}

int	count_number_single_quotes(char *input)
{
	size_t	i;
	int		count_single_quotes;

	i = 0;
	count_single_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			count_single_quotes++;
		i++;
	}
	return (count_single_quotes);
}

int	check_if_unclosed_quotes(char *input)
{
	int	count_double_quotes;
	int	count_single_quotes;

	count_double_quotes = count_number_double_quotes(input);
	count_single_quotes = count_number_single_quotes(input);
	if (count_double_quotes % 2 != 0)
	{
		ft_printf("minishell: syntax error, odd number of double quotes\n");
		return (UNCLOSED_QUOTES);
	}
	if (count_single_quotes % 2 != 0)
	{
		ft_printf("minishell: syntax error, odd number of single quotes\n");
		return (UNCLOSED_QUOTES);
	}
	return (EXIT_SUCCESS);
}