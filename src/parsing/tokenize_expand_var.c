/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:26:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/10 16:52:44 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ATTENTION NE PAS OUBLIER DE TRAITER LE CAS $? pour exit !!

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
	int	len;

	len = ft_strlen(word);
	*i += ft_strlen(word);
}

char	*extract_name_after_dollar(char *input, int *i)
{
	char	*extracted_name;
	int		start_index;

	(*i)++; //on avance et on passe le dollar
	start_index = *i;
	while (input[*i])
	{
		if (input[*i] == '$' || ft_isspace(input[*i]) || is_quote(input[*i])) //on stop des qu'on trouve un autre $, un espace ou une quote
			break;
		(*i)++;
	}
	extracted_name = ft_substr(input, start_index, *i - start_index);
	if (!extracted_name)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return (NULL);
	}
	update_index(i, extracted_name);
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

char	*compress_spaces(char *str)
{
	char	*dest;
	int		in_word;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	in_word = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isspace(str[i]))
		{
			dest[j++] = str[i++];
			in_word = 1;
		}
		else if (in_word == 1)
		{
			dest[j] = ' ';
			in_word = 0;
			i++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

void	handle_quote(char *input, int *i, char *open_quote)
{
	if (*open_quote == '\0')
		*open_quote = input[*i];
	else if (input[*i] == *open_quote)
		*open_quote = '\0';
}

char	*handle_dollar_sign(char *input, int *i, t_env **env, char *expanded_var)
{
	char	*extracted_name;

	extracted_name = extract_name_after_dollar(input, &i);
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
	final_string = ft_strjoin(final_string, "0123456789");
	*i += 10;
	return (final_string);
	// A CHANGER PAR RAPPORT A L'EXIT
}

char	*expand_double_quote(char *final_string, char *input, int *i, t_env **env)
{
	char	*expanded_var;

	expanded_var = handle_dollar_sign(&input, &i, env, &expanded_var);
	if (!expanded_var)
		return (NULL);
	final_string = ft_strjoin(final_string, expanded_var);
	free(expanded_var);
	return (final_string);
}

char	*expand_without_quote(char *final_string, char *input, int *i, t_env **env)
{
	char	*expanded_var;

	expanded_var = handle_dollar_sign(&input, &i, env, &expanded_var);
	if (!expanded_var)
		return (NULL);
	expanded_var = compress_spaces(&expanded_var, &i);
	expanded_var = remove_spaces(&expanded_var, &i);
	final_string = ft_strjoin(final_string, expanded_var);
	return (final_string);
}

// char	*expand_var_depending_quote(char *final_string, char *open_quote, int *i, t_env **env)
// {
// 	if (input[i + 1] == '?')
// 	{
// 		final_string = handle_exit_error();
// 		i++; //? je dois avancer de combien par rapport a la fonction ?
// 	}
// 	if (open_quote == DOUBLE_QUOTE)
// 		final_string = expand_double_quote(&final_string, &input, &i, env);
// 	else if (!open_quote)
// 		final_string = expand_without_quote(&final_string, &input, &i, env);
// }


char	*search_and_replace(char *input, t_env **env)
{
	char	*final_string;
	char	*open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	final_string = ft_strdup("");
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			handle_quote(&input, &i, &open_quote);
			final_string = str_append(final_string, input[i]);
			i++;
		}
		else if (input[i] == '$' && open_quote != SINGLE_QUOTE)
		{
			if (input[i + 1] == '?')
			{
				final_string = handle_exit_error();
				i++; //? je dois avancer de combien par rapport a la fonction ?
			}
			if (open_quote == DOUBLE_QUOTE)
				final_string = expand_double_quote(&final_string, &input, &i, env);
			else if (!open_quote)
				final_string = expand_without_quote(&final_string, &input, &i, env);
		}
		else
		{
			final_string = str_append(final_string, input[i]);
			i++;
		}
		//pas de i++ ici ? gestion dans les fonctions expand > on met i a la fin du mot expanded
	}
	return (final_string);
}

t_token_node	*expand_input(t_token_node **token_list, t_env **env_final)
{
	t_token_node	*temp;
	char			*new_string;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type != TOKEN_PIPE)
		{
			new_string = search_and_replace(temp->value, env_final);
			if (!new_string)
				return (NULL); //free tous les autres noeuds qui ont ete modif ?
			free(temp->value);
			temp->value = new_string;
		}
		temp = temp->next;
	}
	return (*token_list);
}
