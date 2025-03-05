/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:44 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 15:12:13 by racoutte         ###   ########.fr       */
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

char	*check_direct_path(char *cmd, t_exec *ex, t_env **env)
{
	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			else
			{
				print_error(cmd);
				free_exec_list(&ex);
				free_env_list(env);
				exit(126);
			}
		}
		else
		{
			print_error(cmd);
			free_exec_list(&ex);
			free_env_list(env);
			exit(127);
		}
	}
	return (NULL);
}

char	*get_path(t_env *env, char *cmd, t_exec *ex)
{
	char	**full_paths;
	char	*path;
	char	*direct_path;

	direct_path = check_direct_path(cmd, ex, &env);
	if (direct_path)
		return (direct_path);
	full_paths = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0 && env->key[4] == '\0')
		{
			full_paths = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (!full_paths)
		return (NULL);
	path = is_path_exec(cmd, full_paths);
	return (path);
}
