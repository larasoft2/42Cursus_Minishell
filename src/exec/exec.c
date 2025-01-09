/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/09 19:13:18 by lusavign         ###   ########.fr       */
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

void	ft_process(t_env *env, t_exec *ex, int *pipefd)
{
	int	pipfd[2];
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
        perror(strerror(errno));
        ft_close_fd(pipefd);
		return ;
	}
    if (pid == 0)
    {
        if (redirect() == 0)
			//blabla;
        ft_execute();
    }
	return ;
}

void    ft_fork(t_env *env, t_exec *ex)
{
    char    **envp_ar;
    
    envp_ar = put_env_in_ar(env);
	while (ex)
	{
    	if (ex && ex->next == NULL) //if 1 cmd & builtin, exec immediately
    	{
        	if (is_builtin(ex, env)) 
        	{
            	ft_free_array(envp_ar);
            	return ;
        	}
        	ft_free_array(envp_ar);
        	return ;
   		}
		else if (ft_process())
			return ;
	}
	while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    {
    } 
	ft_free_array(envp_ar);
	return ;
}

	// if (pipe(pipefd) == -1)
	// {
	// 	ft_close_fd(pipefd);
	// 	return ;
	// }
    // while (ex)
    // {
    //     pid = fork();
    //     if (pid == -1)
    //     {
    //         perror(strerror(errno));
    //         ft_close_fd(pipefd);
    //         return ;
    //     }
    //     if (pid == 0)
    //     {
    //         ft_process(env, ex, pipefd); //close fds? //reverif builtin dedans
    //         return ;
    //     }
    //     ex = ex->next;
    // }
    // while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    // {
    // } 
    // ft_close_fd(pipefd);

// void	ft_redirect(char **av, int *pipefd, int filetype)
// {
// 	int	fd;

// 	fd = ft_open(av, filetype, pipefd);
// 	if (filetype == 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 	}
// 	else
// 	{
// 		dup2(pipefd[0], STDIN_FILENO);
// 		dup2(fd, STDOUT_FILENO);
// 	}
// 	close(fd);
// 	ft_close_fd(pipefd);
// }



// 	// check errors, parsing???