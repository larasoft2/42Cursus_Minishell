/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/21 18:25:50 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Les arguments seront places dans un tableau **,
// donc je verifie si un arg du tab fait ref a un builtin

// // The  getenv()  function searches the environment list to find the
// environment variable name,
// and returns a pointer to the corresponding value string.

// int is_builtin(t_exec *ex)
// {
// 	if (!ex || !ex->arg || !ex->arg[0])
// 		return (-1);
// 	while (ex)
// 	{
// 		if (ft_strcmp(ex->arg[0], "echo") == 0)
// 			return (1);
// 		//else if (ft_strcmp(ex->arg[0], "cd") == 0)
// 			// return (1);
// 		else if (ft_strcmp(ex->arg[0], "pwd") == 0)
// 			return (1);
// 		//else if (ft_strcmp(ex->arg[0], "export") == 0)
// 		//	return (1);
// 		else if (ft_strcmp(ex->arg[0], "unset") == 0)
// 			return (1);
// 		else if (ft_strcmp(ex->arg[0], "env") == 0)
// 			return (1);
// 		ex = ex->next;
// 	}
// 	return (-1);
// }

int	exec_builtin(t_exec *ex, t_env *env)
{
	if (!ex || !ex->arg || !ex->arg[0])
		return (-1);
	while (ex)
	{
		// if (ex->type == TOKEN_WORD)
		if (ft_strcmp(ex->arg[0], "echo") == 0)
			ft_echo(ex, 0);
		//else if (ft_strcmp(ex->arg[0], "cd") == 0)
		//	ft_cd(tmp);
		else if (ft_strcmp(ex->arg[0], "pwd") == 0)
			ft_pwd(0);
		//else if (ft_strcmp(ex->arg[0], "export") == 0)
		//	ft_export(tmp);
		else if (ft_strcmp(ex->arg[0], "unset") == 0)
			ft_unset(env, ex);
		else if (ft_strcmp(ex->arg[0], "env") == 0)
			ft_env(env);
		//else if (ft_strcmp(ex->arg[0], "cd") == 0)
		//	ft_exit(tmp);
		ex = ex->next;
	}
	return (-1);
}
