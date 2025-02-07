/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var_handle_dollar.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:04 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/07 19:11:09 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var(char *name, t_env **env)
{
	t_env	*temp;
	char	*new_name;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strcmp(name, temp->key) == 0)
		{
			if (!temp->value)
				return (ft_strdup(""));
			new_name = ft_strdup(temp->value);
			return (new_name);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}

char	*extract_name_after_dollar(char *input, int *i)
{
	char	*extracted_name;
	int		start_index;

	(*i)++;
	start_index = *i;
	while (input[*i])
	{
		if (is_var_stop_char(input[*i]) || ft_isspace(input[*i])
			|| is_quote(input[*i]))
			break ;
		(*i)++;
	}
	extracted_name = ft_substr(input, start_index, *i - start_index);
	if (!extracted_name)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return (NULL);
	}
	return (extracted_name);
}

char	*handle_dollar_sign(char *input, int *i, t_env **env,
	char *expanded_var)
{
	char	*extracted_name;

	extracted_name = extract_name_after_dollar(input, i);
	if (!extracted_name)
		return (NULL);
	expanded_var = expand_env_var(extracted_name, env);
	free(extracted_name);
	if (!expanded_var)
		return (NULL);
	return (expanded_var);
}

char	*handle_exit_error(char *final_string, int *i)
{
	final_string = ft_strjoin(final_string, "1234567");
	(*i)++;
	return (final_string);
}

char	*expand(char *final_string, char *input, int *i, t_env **env)
{
	char	*expanded_var;
	char	*temp;

	expanded_var = NULL;
	expanded_var = handle_dollar_sign(input, i, env, expanded_var);
	if (!expanded_var)
		return (NULL);
	temp = ft_strjoin(final_string, expanded_var);
	if (!temp)
		return (NULL);
	free(expanded_var);
	free(final_string);
	return (temp);
}
