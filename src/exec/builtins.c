/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:57:10 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 17:45:17 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_exec *ex)
{
	t_exec	*temp;

	temp = ex;
	if (!ex || !ex->arg || !ex->arg[0])
		return (-1);
	while (temp)
	{
		if (ft_strcmp(temp->arg[0], "echo") == 0
			|| ft_strcmp(temp->arg[0], "cd") == 0
			|| ft_strcmp(temp->arg[0], "pwd") == 0
			|| ft_strcmp(temp->arg[0], "export") == 0
			|| ft_strcmp(temp->arg[0], "unset") == 0
			|| ft_strcmp(temp->arg[0], "env") == 0
			|| ft_strcmp(temp->arg[0], "exit") == 0)
			return (1);
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	return (-1);
}

int	exec_builtin(t_exec *ex, t_env **env, int *std_dup)
{
	t_exec	*temp;

	temp = ex;
	if (!ex || !ex->arg || !ex->arg[0])
		return (-1);
	while (temp)
	{
		if (ft_strcmp(temp->arg[0], "echo") == 0)
			ft_echo(temp);
		else if (ft_strcmp(temp->arg[0], "cd") == 0)
			ft_cd(temp, *env);
		else if (ft_strcmp(temp->arg[0], "pwd") == 0)
			ft_pwd(STDOUT_FILENO);
		else if (ft_strcmp(temp->arg[0], "export") == 0)
			ft_export(temp, env);
		else if (ft_strcmp(temp->arg[0], "unset") == 0)
			ft_unset(temp, env);
		else if (ft_strcmp(temp->arg[0], "env") == 0)
			ft_env(temp, *env);
		else if (ft_strcmp(temp->arg[0], "exit") == 0)
			ft_exit(ex, *env, std_dup);
		temp = temp->next;
	}
	return (-1);
}
