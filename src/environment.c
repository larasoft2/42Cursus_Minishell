/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:00:34 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/19 20:10:03 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_env *head)
{
	t_env	*cleaner;

	if (!head)
		return ;
	while (head)
	{
		cleaner = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = cleaner;
	}
}

char	**put_env_in_ar(t_env *envp)
{
	char	**array_env;
	int		i;
	char	*str;

	i = 0;
	if (!envp)
		return (NULL);
	array_env = malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	while (envp)
	{
		str = ft_strjoin(envp->key, "=");
		str = ft_strjoin(str, envp->value);
		array_env[i++] = str;
		envp = envp->next;
		str = NULL;
	}
	return (array_env);
}

t_env	*create_list(char *key, char *value)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
	{
		perror(strerror(errno));
		return (NULL);
	}
	list->key = key;
	list->value = value;
	list->next = NULL;
	return (list);
}

void	append_list(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_list(key, value);
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

t_env	*get_env_list(char **realenv)
{
	int		i;
	char	*value;
	char	*pos;
	char	*key;
	t_env	*envp;

	i = 0;
	envp = NULL;
	while (realenv[i])
	{
		pos = ft_strchr(realenv[i], '=');
		if (pos)
		{
			key = ft_strndup(realenv[i], pos - realenv[i]);
			value = ft_strdup(pos + 1);
			append_list(&envp, key, value);
		}
		i++;
	}
	return (envp);
}

// int	main(int ac, char **av, char **realenv)
// {
// 	t_env	*envp;

// 	(void)ac;
// 	(void)av;
// 	envp = get_env_list(realenv);
// 	print_list(envp);
// 	ft_free_list(envp);
// }
