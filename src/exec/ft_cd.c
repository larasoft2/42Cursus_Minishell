/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:09 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/12 19:21:11 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// cd with only relative or absolute	path;
// changes the current working directory

// chdir

void	ft_cd(t_env *env, t_ast *ast)
{
	while (env)
	{
		if (ft_strcmp(env->key, ast->arg[0]) == 0)
		{
			chdir(env->value);
		}
		env = env->next;
	}
}