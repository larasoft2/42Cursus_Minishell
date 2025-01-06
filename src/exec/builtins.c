/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/06 22:00:36 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Les arguments seront places dans un tableau **,
// donc je verifie si un arg du tab fait ref a un builtin

// // The  getenv()  function searches the environment list to find the
// environment variable name,
// and returns a pointer to the corresponding value string.

// int	is_builtin(t_exec *ex)
// {
// 	int	tmp;

// 	tmp = 0;
// 	while (ex)
// 	{
// 		// if (ex->type == TOKEN_WORD)
// 		if (ft_strcmp(ex->arg[0], "echo") == 0)
// 			ft_echo(tmp);
// 		else if (ft_strcmp(ex->arg[0], "cd") == 0)
// 			ft_cd(tmp);
// 		else if (ft_strcmp(ex->arg[0] "pwd") == 0)
// 			ft_pwd(tmp);
// 		else if (ft_strcmp(ex->arg[0], "export") == 0)
// 			ft_export(tmp);
// 		else if (ft_strcmp(ex->arg[0], "unset") == 0)
// 			ft_unset(tmp);
// 		else if (ft_strcmp(ex->arg[0], "env") == 0)
// 			ft_env(tmp);
// 		else if (ft_strcmp(ex->arg[0], "cd") == 0)
// 			ft_exit(tmp);
// 		else
// 			ex = ex->next;
// 	}
// 	return (-1);
// }
