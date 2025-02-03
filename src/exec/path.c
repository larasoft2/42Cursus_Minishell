/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:44 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/03 18:22:51 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_path_exec(char *cmd, char **full_paths)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	tmp = NULL;
	path = NULL;
	while (full_paths[++i])
	{
		tmp = ft_strjoin(full_paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			full_paths = ft_free_array(full_paths);
			return (path);
		}
		free(path);
	}
	if (full_paths)
		full_paths = ft_free_array(full_paths);
	return (NULL);
}

char	*get_path(t_env *env, char *cmd)
{
	char	**full_paths;
	char	*path;
	int		i;

	full_paths = NULL;
	path = NULL;
	i = 0;
	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
		return (cmd);
	while (env)
	{
    	if (ft_strncmp(env->key, "PATH", 4) == 0 && env->key[4] == '\0')
   		{
        	full_paths = ft_split(env->value, ':');
        	break;
    	}
    	env = env->next;
	}
	if (!full_paths)
		return (NULL);
	path = is_path_exec(cmd, full_paths);
	return (path);
}
