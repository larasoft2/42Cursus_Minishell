/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/10 19:53:21 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	ft_isbuiltin(t_ast *ast)
{
	if (ft_strcmp(ast->arg[0], "echo") == 0)
		ft_echo();
	else if (ft_strcmp(ast->arg[0], "cd") == 0)
		ft_cd();
	else if (ft_strcmp(ast->arg[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(ast->arg[0], "export") == 0)
		ft_export();
	else if (ft_strcmp(ast->arg[0], "unset") == 0)
		ft_unset();
	else if (ft_strcmp(ast->arg[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(ast->arg[0], "cd") == 0)
		ft_exit();
	else
		return (-1);
}