/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:26:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/27 14:27:56 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_regular_token(t_token_node *token, t_env **env_final)
{
	char	*new_string;

	new_string = search_and_replace(token->value, env_final);
	if (!new_string)
	{
		printf("Erreur: s_a_r NULL pour la valeur : %s\n", token->value);
		return (EXIT_FAILURE);
	}
	free(token->value);
	token->value = new_string;
	return (EXIT_SUCCESS);
}

int	process_heredoc_token(t_token_node *token)
{
	char	*new_string;

	new_string = search_and_replace_heredoc(token->value);
	if (!new_string)
	{
		printf("Erreur: s_a_r_here NULL pour la valeur : %s\n", token->value);
		return (EXIT_FAILURE);
	}
	free(token->value);
	token->value = new_string;
	return (EXIT_SUCCESS);
}

t_token_node	*clean_tokens(t_token_node **token_list, t_env **env_final)
{
	t_token_node	*temp;

	temp = *token_list;
	while (temp != NULL)
	{
		if (temp->type != TOKEN_PIPE && temp->type != TOKEN_REDIR_HEREDOC)
		{
			if (process_regular_token(temp, env_final) == EXIT_FAILURE)
				return (NULL);
		}
		else if (temp->type == TOKEN_REDIR_HEREDOC)
		{
			if (process_heredoc_token(temp) == EXIT_FAILURE)
				return (NULL);
		}
		temp = temp->next;
	}
	return (*token_list);
}

// char	*search_and_replace(char *input, t_env **env)
// {
// 	char	*final_string;
// 	char	open_quote;
// 	int		i;

// 	i = 0;
// 	open_quote = '\0';
// 	final_string = ft_strdup("");
// 	while (input[i])
// 	{
// 		if (is_quote(input[i]))
// 			final_string = handle_quote(input, &i, &open_quote, final_string);
// 		else if (input[i] == '$' && open_quote != '\'')
// 		{
// 			if (input[i + 1] == '?')
// 			{
// 				final_string = handle_exit_error(final_string, &i);
// 				i++;
// 			}
// 			else if (open_quote == '"' && (is_metacharacter(input[i + 1]) || ft_isspace (input[i + 1])))
// 			{
// 				final_string = str_append(final_string, input[i]);
// 				i++;
// 			}
// 			else
// 				final_string = expand(final_string, input, &i, env);
// 		}
// 		else
// 		{
// 			final_string = str_append(final_string, input[i]);
// 			i++;
// 		}
// 	}
// 	return (final_string);
// }

// t_token_node	*clean_tokens(t_token_node **token_list, t_env **env_final)
// {
// 	t_token_node	*temp;
// 	char			*new_string;

// 	temp = *token_list;
// 	while (temp != NULL)
// 	{
// 		if (temp->type != TOKEN_PIPE && temp->type != TOKEN_REDIR_HEREDOC)
// 		{
// 			new_string = search_and_replace(temp->value, env_final);
// 			if (!new_string)
// 			{
// 				printf("Erreur: search_and_replace a retourné NULL pour la valeur : %s\n", temp->value);
// 				return (NULL);
// 			}
// 			free(temp->value);
// 			temp->value = new_string;
// 		}
// 		else if (temp->type == TOKEN_REDIR_HEREDOC)
// 		{
// 			new_string = search_and_replace_heredoc(temp->value);
// 			if (!new_string)
// 			{
// 				printf("Erreur: search_and_replace_heredoc a retourné NULL pour la valeur : %s\n", temp->value);
// 				return (NULL);
// 			}
// 			free(temp->value);
// 			temp->value = new_string;
// 		}
// 		temp = temp->next;
// 	}
// 	return (*token_list);
// }

// void	keep_one_space_at_start(char *str, char *str_trimmed, int *i, int *j)
// {
// 	if (ft_isspace(str[*i]))
// 	{
// 		str_trimmed[(*j)++] = ' ';
// 		while (ft_isspace(str[*i]))
// 			(*i)++;
// 	}
// }

// void	copy_and_compress_spaces(char *str, char *str_trimmed, int *i, int *j)
// {
// 	bool space_added = false;

// 	while (str[*i])
// 	{
// 		if (!ft_isspace(str[*i]))
// 		{
// 			str_trimmed[(*j)++] = str[(*i)++];
// 			space_added = false;
// 		}
// 		else if (!space_added)
// 		{
// 			str_trimmed[(*j)++] = ' ';
// 			space_added = true;
// 			while (ft_isspace(str[*i]))
// 				(*i)++;
// 		}
// 	}
// }

// void	keep_one_space_at_the_end(char *str, char *str_trimmed, int *j)
// {
// 	if (*j > 0 && ft_isspace(str[ft_strlen(str) - 1]) && !ft_isspace(str_trimmed[*j - 1]))
// 		str_trimmed[(*j)++] = ' ';
// }

// char	*strtrim_spaces(char *str)
// {
// 	char	*str_trimmed;
// 	int		i;
// 	int		j;

// 	if (!str)
// 		return (NULL);
// 	str_trimmed = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	if (!str_trimmed)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	keep_one_space_at_start(str, str_trimmed, &i, &j);
// 	copy_and_compress_spaces(str, str_trimmed, &i, &j);
// 	keep_one_space_at_the_end(str, str_trimmed, &j);
// 	str_trimmed[j] = '\0';
// 	return (str_trimmed);
// }
