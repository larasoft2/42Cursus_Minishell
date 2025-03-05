/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:26:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/05 15:15:37 by racoutte         ###   ########.fr       */
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

char	*process_expand(char *input, int *i, char *final_string, t_env **env)
{
	return (handle_dollar_case(input, i, final_string, env));
}
