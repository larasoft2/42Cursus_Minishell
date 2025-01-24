/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:26:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/24 17:01:07 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ATTENTION PROTECTION MALLOC

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
				return (ft_strdup("")); // retourne une chaine vide si la valeur de la var env est NULL
			new_name = ft_strdup(temp->value); // change et met la valeur de la variable d'env
			return (new_name);
		}
		temp = temp->next;
	}
	return (ft_strdup("")); // si la variable (key) n'est pas trouvee, on renvoie une chaine vide
}

void	update_index(int *i, char *word)
{
	*i += ft_strlen(word);
}

int	is_var_stop_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';' || c == '('
		|| c == ')' || c == '`' || c == '$' || c == '#' || c == '=' || c == ':'
		|| c == '/' || c == '[' || c == ']' || c == '{' || c == '}'
		|| c == '%' || c == '^' || c == '\\')
		return (1);
	else
		return (0);
}

char	*extract_name_after_dollar(char *input, int *i)
{
	char	*extracted_name;
	int		start_index;

	(*i)++; //on avance et on passe le dollar
	start_index = *i;
	while (input[*i])
	{
		if (is_var_stop_char(input[*i]) || ft_isspace(input[*i]) || is_quote(input[*i])) //on stop des qu'on trouve un autre $, un espace ou une quote
			break;
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

char	*handle_quote(char *input, int *i, char *open_quote, char *final_string)
{
	if (*open_quote == '\0') //si je n'ai encore aucune quote, je l'ouvre et je ne l'ecris pas (quote structurelle)
	{
		*open_quote = input[*i];
		(*i)++;
	}
	else if (input[*i] == *open_quote) //si j'ai la meme, ca veut dire que je dois la fermer (je ne l'ecris pas, quote structurelle)
	{
		*open_quote = '\0';
		(*i)++;
	}
	else //sinon, c'est une quote litterale (a garder et ecrire), une quote qui n'est pas egale a la valeur stockee dans open_quote
	{
		final_string = str_append(final_string, input[*i]);
		(*i)++;
	}
	return (final_string);
}

char	*handle_dollar_sign(char *input, int *i, t_env **env, char *expanded_var)
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
	final_string = ft_strjoin(final_string, "0"); //attention: free noeuds ??
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
		return (NULL);//free noeuds ?
	free(expanded_var);
	free(final_string);
	return (temp);
}

int	is_metacharacter(char c)
{
	if (c == 35 || (c >= 37 && c <= 41) || c == 47 || c == 59
		|| c == 60 || c == 61 || c == 62 || (c >= 91 && c <= 94) || c == 96
		|| (c >= 123 && c <= 125))
		return (1);
	else
		return (0);
}

char	*search_and_replace(char *input, t_env **env)
{
	char	*final_string;
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	final_string = ft_strdup("");
	while (input[i])
	{
		if (is_quote(input[i]))
			final_string = handle_quote(input, &i, &open_quote, final_string);
		else if (input[i] == '$' && open_quote != '\'')
		{
			if (input[i + 1] == '?')
			{
				final_string = handle_exit_error(final_string, &i);
				i++;
			}
			else if (open_quote == '"' && (is_metacharacter(input[i + 1]) || ft_isspace (input[i + 1])))
			{
				final_string = str_append(final_string, input[i]);
				i++;
			}
			else
				final_string = expand(final_string, input, &i, env);
		}
		else
		{
			final_string = str_append(final_string, input[i]);
			i++;
		}
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

t_token_node	*clean_tokens(t_token_node **token_list, t_env **env_final)
{
	t_token_node	*temp;
	char			*new_string;

	temp = *token_list;
	while (temp != NULL)
	{
		if (temp->type != TOKEN_PIPE && temp->type != TOKEN_REDIR_HEREDOC)
		{
			new_string = search_and_replace(temp->value, env_final);
			if (!new_string)
			{
				printf("Erreur: search_and_replace a retourné NULL pour la valeur : %s\n", temp->value);
				return (NULL); //free tous les autres noeuds qui ont ete modif ?
			}
			free(temp->value);
			temp->value = new_string;
		}
		else if (temp->type == TOKEN_REDIR_HEREDOC)
		{
			new_string = search_and_replace_heredoc(temp->value);
			if (!new_string)
			{
				printf("Erreur: search_and_replace_heredoc a retourné NULL pour la valeur : %s\n", temp->value);
				return (NULL); //free tous les autres noeuds qui ont ete modif ?
			}
			free(temp->value);
			temp->value = new_string;
		}
		temp = temp->next;
	}
	return (*token_list);
}

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

