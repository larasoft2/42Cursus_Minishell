/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:55:03 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/05 18:22:35 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env, t_exec *ex) //unset sans arg ?
{
	t_env	*current;
	t_env	*prev;

	if (!env || !ex || !ex->arg)
		return (1);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, ex->arg[1]) == 0) //[0] might change bc struct?
		{
			if (prev)
				prev->next = current->next;
			else
				(*env)->next = current->next;
			printf("current = %s\n", current->key);
			free(current);
			current = NULL;
			print_env(*env);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
