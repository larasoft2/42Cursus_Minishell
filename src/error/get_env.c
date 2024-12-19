/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:00:34 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/19 16:26:20 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_list(char *key)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
	{
		perror(strerror(errno));
		return (NULL);
	}
	list->key = key;
	list->next = list;
	return (list);
}

void	append_list(t_env **head, char *key)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_list(key);
	if (!new_node)
	{
		perror(strerror(errno));
		return ;
	}
	if (!(*head))
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

t_env	*get_env_list(char **realenv, t_env **envp)
{
	int i;
	int j;
	char *key;

	i = 0;
	j = 0;
	key = NULL;
	while (realenv[i])
	{
		printf("in realenv while\n");
		//	printf("%s\n", realenv[i]);
		if (ft_strcmp(realenv[i], "="))
		{
			printf("in strcmp");
			while (j < i)
			{
				printf("in j < i");
				key = ft_strcpy(realenv[j], key);
				append_list(envp, key);
				printf("%s\n", (*envp)->key);
				j++;
			}
		}
		i++;
	}
	return (*envp);
}