/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/05 16:22:19 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Les arguments seront places dans un tableau **,
// donc je verifie si un arg du tab fait ref a un builtin

// // The  getenv()  function searches the environment list to find the
// environment variable name,
// and returns a pointer to the corresponding value string.

int is_builtin(t_exec *ex)
{
	if (!ex || !ex->arg || !ex->arg[0])
		return (-1);
	while (ex)
	{
		if (ft_strcmp(ex->arg[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(ex->arg[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(ex->arg[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(ex->arg[0], "export") == 0)
			return (1);
		else if (ft_strcmp(ex->arg[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(ex->arg[0], "env") == 0)
			return (1);
		ex = ex->next;
	}
	return (-1);
}

int	exec_builtin(t_exec *ex, t_env **env)
{
	if (!ex || !ex->arg || !ex->arg[0])
		return (-1);
	while (ex)
	{
		if (ft_strcmp(ex->arg[0], "echo") == 0)
			ft_echo(ex);
		else if (ft_strcmp(ex->arg[0], "cd") == 0)
			ft_cd(ex);
		else if (ft_strcmp(ex->arg[0], "pwd") == 0)
			ft_pwd(STDOUT_FILENO);
		else if (ft_strcmp(ex->arg[0], "export") == 0)
			ft_export(ex, env);
		else if (ft_strcmp(ex->arg[0], "unset") == 0)
			ft_unset(env, ex);
		else if (ft_strcmp(ex->arg[0], "env") == 0)
			ft_env(*env);
		ex = ex->next;
		// if (ex != NULL) {
        //     printf("Next command: %s\n", ex->arg[0]);
        // } else {
        //     printf("No next command, exiting.\n");
        // }
	}
	return (-1);
}
