/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:42:56 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/21 19:41:46 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*build_basic_env(t_env *env_final)
{
	char	dir[4096];
	char	*pwd;

	pwd = NULL;
	if (!getcwd(dir, 4096))
		dir[0] = '\0';
	pwd = ft_strjoin("PWD=", dir);
	if (!pwd)
		return (NULL);
	add_var_to_env("SHLVL=1", &env_final);
	add_var_to_env(pwd, &env_final);
	add_var_to_env("OLDPWD=", &env_final);
	free(pwd);
	return (env_final);
}

t_env	*set_env(t_env *env_final, char **env)
{
	if (*env == NULL)
		env_final = build_basic_env(env_final);
	else
		env_final = get_env_list(env);
	return (env_final);
}
