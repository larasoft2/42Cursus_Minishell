/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:55:03 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/12 15:27:45 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	ft_unset(t_env *env, t_ast *ast)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !ast || !ast->arg || !ast->arg[0])
		return (1);
	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, ast->arg[0]) == 0) //[0] might change bc AST
		{
			if (prev)
				prev->next = current->next;
			else
				env->next = current->next;
			free(current);
			current = NULL;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

// void	print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		if (env->key && env->value)
// 			printf("%s=%s\n", env->key, env->value);
// 		else
// 			printf("(unset variable)\n");
// 		env = env->next;
// 	}
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env1;
// 	t_env	*env2;
// 	t_env	*env3;
// 	t_env	*env4;
// 	t_ast	ast;
// 	char	*args[] = {"HOME", "TEST", NULL};

// 	env1 = malloc(sizeof(t_env));
// 	env2 = malloc(sizeof(t_env));
// 	env3 = malloc(sizeof(t_env));
// 	env4 = malloc(sizeof(t_env));
// 	env1->key = strdup("USER");
// 	env1->value = strdup("admin");
// 	env1->next = env2;
// 	env2->key = strdup("HOME");
// 	env2->value = strdup("/home/admin");
// 	env2->next = env3;
// 	env3->key = strdup("IDK");
// 	env3->value = strdup("/bin/bash");
// 	env3->next = env4;
// 	env4->key = strdup("TEST NODE");
// 	env4->value = strdup("/path/path");
// 	env4->next = NULL;
// 	printf("Initial environment:\n");
// 	print_env(env1);
// 	ast.arg = args;
// 	printf("\nCalling ft_unset to remove 'HOME':\n");
// 	ft_unset(env1, &ast);
// 	printf("\nEnvironment after unset:\n");
// 	print_env(env1);
// 	return (0);
// }
