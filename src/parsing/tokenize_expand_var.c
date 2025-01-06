/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:26:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/01/06 18:15:10 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ATTENTION: ajout de la variable quote dans toutes les fonctions pour savoir dans quel cas on est

//SI ON A UN $ SIGN ET
//SI quote = \0 >> EXPAND >> on doit checker les multiples espaces dans la valeur de la variable et les compresser en un seul espace
//SI quote = " >> EXPAND >> tout est garde (espaces aussi)
//SI quote = ' >> PAS EXPAND >> LITTERAL + tout est garde (espaces aussi)

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

char	*search_and_replace(char *input, t_env **env)
{
	char	*new_value;
	char	*name;
	char	*open_quote;
	size_t	i;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (is_quote(input[i]) && !open_quote)
			open_quote = input[i];
		if (input[i] == '$' && is_quote(input[i]) != SINGLE_QUOTE)
		{
			name = extract_name_after_dollar_sign();
			new_value = expand_env_var();
			add_new_value();
		}
		else if (input[i] == '$' && is_quote(input[i]) == SINGLE_QUOTE)
			i++;

		i++;
	}
	//token_list->value : parcourir la chaine du mot
	//prendre en compte les quotes, avec variable qui indique si single ou double ouverte
	//si je rencontre un $ alors autre fonction pour expand si besoin

	//return pointeur sur toute la liste avec les valeurs changees (si c'etait necessaire)
}

t_token_node	*expand_input(t_token_node **token_list, t_env **env_final)
{
	t_token_node	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type != TOKEN_PIPE) //si le type de token n'est pas un pipe, on enclenche la fonction expand pour changer la valeur si besoin
		{
			search_and_replace(&temp->value, env_final);
		}
		temp = temp->next;
	}
	return (temp);
}
