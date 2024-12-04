/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_pipe_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:07:51 by racoutte          #+#    #+#             */
/*   Updated: 2024/12/04 17:21:40 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_starts_or_ends_with_pipe_redir(char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (input[0] == '|' || input[0] == '<' || input[0] == '>')
	{
		ft_printf("minishell: syntax error near unexpected token `%c'\n", input[0]);
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	}
	if (input[len - 1] == '|' || input[len - 1] == '<' || input[len - 1] == '>')
	{
		ft_printf("minishell: syntax error near unexpected token `%c'\n", input[len - 1]);
		return (STARTS_OR_ENDS_WITH_PIPE_REDIR);
	}
	return (EXIT_SUCCESS);
}

int	number_redir_right(char *input)
{
	size_t	i;
	int		count;

	i = 0;
	while (input[i])
	{
		count = 0;
		while (input[i] == '>')
		{
			count++;
			if (count > 2)
			{
				ft_printf("minishell: syntax error near unexpected token `>'\n");
				return (WRONG_NUMBER_REDIR);
			}
			i++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	number_redir_left(char *input)
{
	size_t	i;
	int		count;

	i = 0;
	while (input[i])
	{
		count = 0;
		while (input[i] == '<')
		{
			count++;
			if (count > 2)
			{
				ft_printf("minishell: syntax error near unexpected token `<'\n");
				return (WRONG_NUMBER_REDIR);
			}
			i++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
