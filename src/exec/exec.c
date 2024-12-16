/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/16 18:16:46 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Les arguments seront places dans un tableau **,
// donc je verifie si un arg du tab fait ref a un builtin

// // The  getenv()  function searches the environment list to find the
// environment variable name,
// and returns a pointer to the corresponding value string.

// int	ft_isbuiltin(t_exec *ex)
// {
//  while (ex)
//  {
//    if (ft_strcmp(ex->cmd, "echo") == 0)
//      ft_echo(tmp);
//  else if (ft_strcmp(ex->cmd, "cd") == 0)
// 		ft_cd(tmp);
// 	else if (ft_strcmp(ex->cmd, "pwd") == 0)
// 		ft_pwd(tmp);
// 	else if (ft_strcmp(ex->cmd, "export") == 0)
// 		ft_export(tmp);
// 	else if (ft_strcmp(ex->cmd, "unset") == 0)
// 		ft_unset(tmp);
// 	else if (ft_strcmp(ex->cmd, "env") == 0)
// 		ft_env(tmp);
// 	else if (ft_strcmp(ex->cmd, "cd") == 0)
// 		ft_exit(tmp);
// 	else
//    ex = ex->next;
//  }
//  return (-1);
// }
