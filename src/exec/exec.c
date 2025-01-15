/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/15 19:14:20 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execve will receive cmd path as first arg
// then options and args as second
// env as last
// ft_close_fd at the end

int	ft_open(t_exec *ex, int *pipefd)
{
	int fd;
	if (ex->type && ex->type->type == TOKEN_REDIR_IN)
		fd = open(ARGIN, O_RDONLY);
	if (ex->type && ex->type->type == TOKEN_REDIR_OUT)
		fd = open(ARGOUT, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (ex->type->type == TOKEN_REDIR_IN)
			ft_putendl_fd(ARGIN, STDERR_FILENO);
		else if (ex->type->type == TOKEN_REDIR_OUT)
			ft_putendl_fd(ARGOUT, STDERR_FILENO);
		ft_close_fd(pipefd);
		exit(1);
	}
	return (fd);
}

void	ft_redirect(t_exec *ex)
{
	int		pipefd[2];
	pid_t	pid;

	// errors are handled here in pipex
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed\n");
		exit(1);
	}
	while (ex)


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
				printf("command not found: %s\n", cmd->arg[0]); //stderr
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