/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:55:03 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/13 15:53:55 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_env(t_env **env, char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_exec *ex, t_env **env)
{
	size_t	i;

	i = 1;
	if (!env || !ex || !ex->arg || !ex->arg[1])
		return (modify_value_exit_code(0), EXIT_SUCCESS); //renvoi silencieux, retourne 0 car c'est l'exit code qu'on doit renvoyer, pas de message d'erreur
	while (ex->arg[i])
	{
		if (check_if_var_name_is_valid(ex->arg[i]) == EXIT_FAILURE)
		{
			printf("invalid var_name: %s\n", ex->arg[i]);
			return (modify_value_exit_code(0), EXIT_FAILURE);
		}
		else
			remove_from_env(env, ex->arg[i]);
		i++;
	}
	return (modify_value_exit_code(0), EXIT_SUCCESS);
}

// int	ft_unset(t_env **env, t_exec *ex) //unset sans arg ?
// {
// 	t_env	*current;
// 	t_env	*prev;

// 	if (!env || !ex || !ex->arg)
// 		return (1);
// 	current = *env;
// 	prev = NULL;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, ex->arg[1]) == 0) //[0] might change bc struct?
// 		{
// 			if (prev)
// 				prev->next = current->next;
// 			else
// 				(*env)->next = current->next;
// 			printf("current = %s\n", current->key);
// 			free(current);
// 			current = NULL;
// 			print_env(*env);
// 			return (0);
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// 	return (1);
// }


