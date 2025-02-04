/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:44:04 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/27 17:43:05 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append(char *str, char c)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
	{
		ft_putstr_fd("Error: Memory allocation failes\n", STDERR_FILENO);
		return (NULL);
	}
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

void	update_index(int *i, char *word)
{
	*i += ft_strlen(word);
}

int	is_var_stop_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';' || c == '('
		|| c == ')' || c == '`' || c == '$' || c == '#' || c == '='
		|| c == ':' || c == '/' || c == '[' || c == ']' || c == '{' || c == '}'
		|| c == '%' || c == '^' || c == '\\')
		return (1);
	else
		return (0);
}

int	is_metacharacter(char c)
{
	if ((c >= 35 && c <= 41) || c == 47 || (c >= 58 && c <= 61) || c == 62
		|| (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 125))
		return (1);
	else
		return (0);
}
