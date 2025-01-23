/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/23 19:20:22 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// execve will receive cmd path as first arg
// then options and args as second
// env as last
// ft_close_fd at the end

// int ft_redirections(t_exec *ex, char *redirect[])
// {
// 	t_token_node  *current;
// 	int		append_flag;

// 	redirect[0] = NULL;
// 	redirect[1] = NULL;
// 	append_flag = 0;
// 	if (!ex || !ex->type)
// 		return (append_flag);
// 	current = ex->type;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_REDIR_IN)
// 			redir_in = ex->arg

// 	}

// }

// int	ft_open(int *pipefd)
// {
// 	int fd;
// 	if (ex->type && ex->type->type == TOKEN_REDIR_IN)
// 		fd = open(ex->arg[0], O_RDONLY);
// 	if (ex->type && ex->type->type == TOKEN_REDIR_OUT)
// 		fd = open(ex->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		if (ex->type->type == TOKEN_REDIR_IN)
// 			ft_putendl_fd(ex->arg[0], STDERR_FILENO);
// 		else if (ex->type->type == TOKEN_REDIR_OUT)
// 			ft_putendl_fd(ex->arg[0], STDERR_FILENO);
// 		ft_close_fd(pipefd);
// 		exit(1);
// 	}
// 	return (fd);
// }

// void	ft_redirect(t_exec *ex)
// {
// 	int		pipefd[2];
// 	pid_t	pid;

// 	// errors are handled here in pipex
// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe failed\n");
// 		exit(1);
// 	}
// 	while (ex)


// }



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


// c le dup pour la suit
			// if (cmd->fd_in != -1)
			// {
    		// 	// dup2(cmd->fd_in, STDIN_FILENO);
    		// 	// close(cmd->fd_in);
			// }
			// else
    		// 	dup2(in_fd, STDIN_FILENO);
			// if (cmd->fd_out != -1) 
			// {
           	// 	// dup2(cmd->fd_out, STDOUT_FILENO);
            // 	// close(cmd->fd_out);
        	// }
			// else if (cmd->next)
        	// 	dup2(pipefd[1], STDOUT_FILENO);


void print_exec_args(t_exec *ex)
{
    while (ex)
    {
        printf("Arguments for command:\n");
        for (int i = 0; ex->arg && ex->arg[i]; i++)
            printf("  [%d]: %s\n", i, ex->arg[i]);
        ex = ex->next;
    }
}



void	ft_fork(t_exec *cmd, t_env **env, int *pipefd)
{
	int	in_fd = 0;
	pid_t	pid;
	char *path_cmd;

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
			ft_close_fd(pipefd);
			path_cmd = get_path(*env, cmd->arg[0]);
			if (!path_cmd)
			{
				printf("command not found: %s\n", cmd->arg[0]); //stderr
				return ;
			}
			printf("ABSOLUTE PATH: %s\n", path_cmd); //remove later
			printf("RELATIVE PATH: %s\n", cmd->arg[0]); //remove later
        	execve(path_cmd, cmd->arg, put_env_in_ar(*env));
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

void ft_error(t_token_node *token, int *pipefd)
{
    ft_putstr_fd(strerror(errno), STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (token && (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT 
	|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC))
        ft_putendl_fd(token->value, STDERR_FILENO);
    else
        ft_putendl_fd("Invalid redirection or command.", STDERR_FILENO);
    ft_close_fd(pipefd);
    //exit(1);
}

int	count_redir(t_exec *ex)
{
	int	i;

	if (!ex)
		return (0);
	i = 0;
	while (ex)
	{
		if (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_OUT)
			return (1);
		ex = ex->next;
	}
	return (-1);
}

void ft_redir(t_exec *ex) //need dup2 to make it work
{
    if (ex->type == TOKEN_REDIR_IN) 
    {
        ex->fd_in = open(ex->arg[0], O_RDONLY);
        if (ex->fd_in < 0) 
        {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
    } 
    else if (ex->type == TOKEN_REDIR_OUT || ex->type == TOKEN_REDIR_APPEND) 
    {
        ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (ex->fd_out < 0)
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        ex->fd_in = STDIN_FILENO;
        ex->fd_out = STDOUT_FILENO;
    }
}


void	ft_init(t_exec *ex)
{
    ex->fd_in = STDIN_FILENO;
    ex->fd_out = STDOUT_FILENO;
}

void    ft_process(t_env **env, t_exec *ex)
{
	int 	command_nb;
	int		fd;
	int		pipefd[2];

	fd = 0;
    if (pipe(pipefd) == -1)
	{
    	perror("pipe failed");
    	exit(1);
	}
	ft_init(ex);
	command_nb = count_command(ex);
	//print_exec_args(ex);
	while (ex)
	{
		printf("COMMAND COUNT: %i\n", command_nb);
    	if ((command_nb == 1) && (is_builtin(ex) == 1))
    	{
			printf("found a builtin + 1 cmd\n");
			exec_builtin(ex, env);
            return ;
        }
		else
		{
			ft_redir(ex);
			ex->fd_in = fd;
			ft_fork(ex, env, pipefd);
		 	return ;
		}
		ex = ex->next;
	}
	while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    {
    }
	ft_close_fd(pipefd);
	return ;
}
