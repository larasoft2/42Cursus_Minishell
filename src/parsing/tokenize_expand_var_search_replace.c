/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var_search_replace.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:26:55 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/20 19:22:15 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quote(char *input, int *i, char *open_quote, char *final_string)
{
	if (*open_quote == '\0')
	{
		*open_quote = input[*i];
		(*i)++;
	}
	else if (input[*i] == *open_quote)
	{
		*open_quote = '\0';
		(*i)++;
	}
	else
	{
		final_string = str_append(final_string, input[*i]);
		(*i)++;
	}
	return (final_string);
}

char	*handle_special_case(char *input, int *i, char open_quote,
	char *final_string)
{
	if (input[*i + 1] == '?')
	{
		final_string = handle_exit_error(final_string, i);
		(*i)++;
	}
	else if (open_quote == '"' && (is_metacharacter(input[*i + 1])
			|| ft_isspace(input[*i + 1])))
			final_string = str_append(final_string, input[(*i)++]);
	return (final_string);
}

char	*dollar_special_cases(char *input, int *i, char open_quote,
	char *final_string)
{
	if (ft_isdigit(input[*i + 1]))
	{
		(*i)++;
		while (ft_isdigit(input[*i]))
			(*i)++;
	}
	else if (is_quote(input[*i + 1]) != '\0' && open_quote == '\0')
		(*i)++;
	else if (input[*i + 1] == '?' || (open_quote == '"'
			&& (is_metacharacter(input[*i + 1]) || ft_isspace(input[*i + 1]))))
		final_string = handle_special_case(input, i, open_quote, final_string);
	else if (input[*i + 1] == '\0' || ft_isspace(input[*i + 1])
		|| is_metacharacter(input[*i + 1]) || input[*i + 1] == '"')
	{
		final_string = str_append(final_string, input[(*i)++]);
	}
	else
		return (NULL);
	return (final_string);
}

char	*handle_dollar_case(char *input, int *i, char *final_string, t_env **env)
{
	char	*result;

	result = dollar_special_cases(input, i, *final_string, final_string);
	if (!result)
		return (expand(final_string, input, i, env));
	return (result);
}

char	*process_expand(char *input, int *i, char *final_string, t_env **env)
{
	return (handle_dollar_case(input, i, final_string, env));
}

char	*search_and_replace(char *input, t_env **env)
{
	char	*final_string;
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	final_string = ft_strdup("");
	if (!final_string)
		return (NULL);
	while (input[i])
	{
		if (is_quote(input[i]))
			final_string = handle_quote(input, &i, &open_quote, final_string);
		else if (input[i] == '$' && open_quote != '\'')
			final_string = process_expand(input, &i, final_string, env);
		else
			final_string = str_append(final_string, input[i++]);
	}
	return (final_string);
}

char	*search_and_replace_heredoc(char *input)
{
	char	*final_string;
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	final_string = ft_strdup("");
	if (!final_string)
		return (NULL);
	while (input[i])
	{
		if (is_quote(input[i]))
			final_string = handle_quote(input, &i, &open_quote, final_string);
		else
		{
			final_string = str_append(final_string, input[i]);
			i++;
		}
	}
	return (final_string);
}

// char	*search_and_replace(char *input, t_env **env)
// {
// 	char	*final_string;
// 	char	*result;
// 	char	open_quote;
// 	int		i;

// 	i = 0;
// 	open_quote = '\0';
// 	result = NULL;
// 	final_string = ft_strdup("");
// 	while (input[i])
// 	{
// 		if (is_quote(input[i]))
// 			final_string = handle_quote(input, &i, &open_quote, final_string);
// 		else if (input[i] == '$' && open_quote != '\'')
// 		{
// 			result = dollar_special_cases(input, &i, open_quote, final_string);
// 			if (!result)
// 				final_string = expand(final_string, input, &i, env);
// 			else
// 				final_string = result;
// 		}
// 		else
// 			final_string = str_append(final_string, input[i++]);
// 	}
// 	return (final_string);
// }
