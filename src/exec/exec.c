/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/14 22:13:27 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_process(t_exec *cmd, t_env *env)//handle pipe after 
{
	int	pipefd[2];
	int	in_fd = 0;
	pid_t	pid;
	char *path_cmd;

	if (pipe(pipefd) == -1)
	{
    	perror("pipe failed");
    	exit(1);
	}
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{	
        perror(strerror(errno));
        ft_close_fd(pipefd);
		return ;
		}
    	if (pid == 0)
    	{
        if (cmd->fd_in != -1) 
		{
            dup2(cmd->fd_in, STDIN_FILENO);
			if (cmd->fd_in >= 0)
        		close(cmd->fd_in);
        } 
		else 
        	dup2(in_fd, STDIN_FILENO);
		if (cmd->fd_out != -1) 
		{
            dup2(cmd->fd_out, STDOUT_FILENO);
			if (cmd->fd_in >= 0)
            	close(cmd->fd_out);
        }
		else if (cmd->next)
        	dup2(pipefd[1], STDOUT_FILENO);
		ft_close_fd(pipefd);
		path_cmd = get_path(env, cmd->arg[0]);
		if (!path_cmd)
		{
			printf("command not found: %s\n", cmd->arg[0]);
			return ;
		}
		printf("PATH: %s\n", cmd->arg[0]);
        execve(get_path(env, cmd->arg[0]), cmd->arg, put_env_in_ar(env));
        perror("execve");
        exit(EXIT_FAILURE);
    	} 
		else if (pid > 0) 
		{
        	waitpid(pid, NULL, 0);
        	close(pipefd[1]);
        	in_fd = pipefd[0];
    	}
		else
		{
    	    perror("fork");
        	return;
    	}
		cmd = cmd->next;
	}
    
}


void    ft_fork(t_env *env, t_exec *ex)
{
	int 	command_nb;
    
	command_nb = count_command(ex);
	while (ex)
	{
    	if ((command_nb == 1) && (is_builtin(ex) == 1))
    	{
			exec_builtin(ex, env);
            return ;
        }
		else
		{
			ft_process(ex, env);
		 	return ;
		}
		ex = ex->next;
	}
	while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    {
    } 
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