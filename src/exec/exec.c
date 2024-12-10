/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/10 21:34:51 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Les arguments seront places dans un tableau **,
// donc je verifie si le premier argument fait ref a un builtin

// // The  getenv()  function searches the environment list to find the
// environment variable name,
// and returns a pointer to the corresponding value string.

// int	ft_isbuiltin(t_ast *ast)
// {
// 	if (ft_strcmp(ast->arg[0], "echo") == 0)
// 		ft_echo(tmp);
// 	// else if (ft_strcmp(ast->arg[0], "cd") == 0)
// 	//	ft_cd(tmp);
// 	else if (ft_strcmp(ast->arg[0], "pwd") == 0)
// 		ft_pwd(tmp);
// 	// else if (ft_strcmp(ast->arg[0], "export") == 0)
// 	//	ft_export(tmp);
// 	// else if (ft_strcmp(ast->arg[0], "unset") == 0)
// 	//	ft_unset(tmp);
// 	// else if (ft_strcmp(ast->arg[0], "env") == 0)
// 	//	ft_env(tmp);
// 	else if (ft_strcmp(ast->arg[0], "cd") == 0)
// 		ft_exit(tmp);
// 	else
// 		return (-1);
// }