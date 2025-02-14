/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/14 13:07:59 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		env_list_size(t_env *env)
{
    int size;

	size = 0;
    while (env)
	{
        size++;
        env = env->next;
    }
    return (size);
}

void	*ft_free_array(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return (NULL);
	while (ar[i])
		i++;
	while (i > 0)
		free(ar[--i]);
	free(ar);
	ar = NULL;
	return (NULL);
}

// void	ft_free_list(t_env *head)
// {
// 	t_env	*cleaner;

// 	if (!head)
// 		return ;
// 	while (head)
// 	{
// 		cleaner = head->next;
// 		free(head->key);
// 		free(head->value);
// 		free(head);
// 		head = cleaner;
// 	}
// }

char	**put_env_in_ar(t_env *envp)
{
	char	**array_env;
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!envp)
		return (NULL);
	array_env = malloc(sizeof(char *) * (env_list_size(envp) + 1));
	while (envp)
	{
		tmp = ft_strjoin(envp->key, "=");
		if (!tmp)
		{
			ft_free_array(array_env);
			return (NULL);
		}
		str = ft_strjoin(tmp, envp->value);
		free(tmp);
		if (!str)
		{
			ft_free_array(array_env);
			return (NULL);
		}
		array_env[i++] = str;
		envp = envp->next;
		str = NULL;
	}
	array_env[i] = NULL;
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
	list->key = ft_strdup(key);
	list->value = ft_strdup(value);
	if (!list->key || !list->value)
	{
		free(list->key);
		free(list->value);
		free(list);
		return (NULL);
	}
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
	free(key);
	free(value);
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
			if (!key || !value)
			{
				free(key);
				free(value);
				return (NULL);
			}
			append_list(&envp, key, value);
		}
		i++;
	}
	return (envp);
}

// int	main(int ac, char **av, char **realenv)
// {
// 	t_env	*envp;
// 	char	**ar;
// 	int		i;

// 	i = 0;
// 	(void)ac;
// 	(void)av;
// 	envp = get_env_list(realenv);
// 	print_list(envp);
// 	ar = put_env_in_ar(envp);
// 	while (ar[i])
// 	{
// 		printf("%s\n", ar[i]);
// 		i++;
// 	}
// 	ft_free_list(envp);
// 	ft_free_array(ar);
// 	ar = NULL;
// }
