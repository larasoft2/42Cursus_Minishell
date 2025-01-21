/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/08 19:19:12 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// execve will receive cmd path as first arg
// then options and args as second
// env as last

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
	while (env->key[i])
	{
		if (ft_strncmp(&env->key[i], "PATH=", 5) == 0)
		{
			full_paths = ft_split(&env->value[i], ':');
			break ;
		}
		i++;
	}
	if (!full_paths)
		return (NULL);
	path = is_path_exec(cmd, full_paths);
	return (path);
}

void    ft_fork(t_env *env, t_exec *ex)
{
    pid_t   pid;
    int     pipefd[2];
    char    **envp_ar;
    
    envp_ar = put_env_in_ar(env);
    if (ex && ex->next == NULL)
    {
        if (is_builtin(ex, env))
        {
            ft_free_array(envp_ar);
            return ;
        }
        ft_free_array(envp_ar);
        return ;
    }
	if (pipe(pipefd) == -1)
	{
		ft_close_fd(pipefd);
		return ;
	}
    while (ex)
    {
        pid = fork();
        if (pid == -1)
        {
            perror(strerror(errno));
            ft_close_fd(pipefd);
            return ;
        }
        if (pid == 0)
        {
            //ft_process(env, ex, pipefd, TEST); //close fds? //reverif builtin dedans
            return ;
        }
        ex = ex->next;
    }
    while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    {
    } 
    ft_close_fd(pipefd);
}

void	ft_process(t_env *env, t_exec *ex, int *pipefd)
{
	(void)ex;
	(void)env;
    if (pipe(pipefd) == -1) //before/after builtin check?
    {
        ft_close_fd(pipefd);
        return ;
    }
}

// 	// check errors, parsing???