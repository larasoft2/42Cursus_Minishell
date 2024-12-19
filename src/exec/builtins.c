/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/19 16:26:50 by lusavign         ###   ########.fr       */
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
// 		if (ft_strcmp(ex->arg, "echo") == 0)
// 			ft_echo(tmp);
// 		else if (ft_strcmp(ex->arg, "cd") == 0)
// 			ft_cd(tmp);
// 		else if (ft_strcmp(ex->arg, "pwd") == 0)
// 			ft_pwd(tmp);
// 		else if (ft_strcmp(ex->arg, "export") == 0)
// 			ft_export(tmp);
// 		else if (ft_strcmp(ex->arg, "unset") == 0)
// 			ft_unset(tmp);
// 		else if (ft_strcmp(ex->arg, "env") == 0)
// 			ft_env(tmp);
// 		else if (ft_strcmp(ex->arg, "cd") == 0)
// 			ft_exit(tmp);
// 		else
// 			ex = ex->next;
// 	}
// 	return (-1);
// }
