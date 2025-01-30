/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/30 18:33:37 by lusavign         ###   ########.fr       */
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

// 	// check errors, parsing???

// void ft_redir(t_exec *ex, int *pipefd) //if parent dup2 fail > exit
// {
// 	ft_open(ex, pipefd);
// 	if (ex->fd_in != STDIN_FILENO)
// 	{
// 		if (dup2(ex->fd_in, STDIN_FILENO) == -1)
// 		{
// 			perror ("fd_in dup2 error");
// 			ft_close_fd(pipefd);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(ex->fd_in);
// 	}
// 	if (ex->fd_out != STDOUT_FILENO)
// 	{
// 		if (dup2(ex->fd_out, STDOUT_FILENO) == -1)
// 		{
// 			perror ("fd_in dup2 error");
// 			ft_close_fd(pipefd);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(ex->fd_out);
// 	}
// 	if (pipefd)
//     {
//         if (pipefd[0] != -1) 
// 			close(pipefd[0]); // Parent's read end
//         if (pipefd[1] != -1 && dup2(pipefd[1], STDOUT_FILENO) == -1)
//         {
//             perror("dup2 pipe output");
//             ft_close_fd(pipefd);
//             exit(EXIT_FAILURE);
//         }
//         close(pipefd[1]); // Close after duplicating
//     }
// }

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

int	is_redir(t_exec *ex)
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

// access F OK check infiles chez Jean
// redir avant, fo ft open parce que des fois y a des redir mdr
// check if redirs avant exec / builtins / 
// && no pipe if no token pipes // and move jsp quelle partie du code 

void	ft_open(t_exec *ex, int *pipefd)
{
    if (ex->type == TOKEN_REDIR_IN) 
    {
        ex->fd_in = open(ex->arg[0], O_RDONLY);
        if (ex->fd_in < 0) 
        {
            perror("Error opening input file");
            ex->error = 1;
            ft_close_fd(pipefd);
            return;
        }
        dup2(ex->fd_in, STDIN_FILENO);
        close(ex->fd_in);
    } 
    else if ((ex->type == TOKEN_REDIR_OUT && ex->error == 0) 
    || (ex->type == TOKEN_REDIR_APPEND && ex->error == 0)) 
    {
        ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (ex->fd_out < 0)
        {
            perror("Error opening output file");
            ex->error = 1;
            // ft_close_fd(pipefd);
            return;
        }
        dup2(ex->fd_out, STDOUT_FILENO);
        close(ex->fd_out);
    } 
    else 
    {
        ex->fd_in = STDIN_FILENO;
        ex->fd_out = STDOUT_FILENO;
    }
}
 
void ft_fork(t_exec *cmd, t_env **env, int *pipefd)
{
    int in_fd = 0;
    pid_t pid;
    char *path_cmd;
    t_exec *current;
    current = cmd;

    // while (current)
    // {
    //     if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT 
	//     || current->type == TOKEN_REDIR_APPEND)
    //         ft_open(current, pipefd);
    //     current = current->next;
    // }
    while (cmd)
    {
        while (cmd && (cmd->type == TOKEN_REDIR_IN || cmd->type == TOKEN_REDIR_OUT 
		|| cmd->type == TOKEN_REDIR_APPEND))
        {
            cmd = cmd->next;
        }
        if (!cmd || cmd->type != TOKEN_WORD)
            break;
        if (cmd->next && pipe(pipefd) == -1)
        {
            perror("pipe");
            return;
        }
        pid = fork();
        if (pid == -1)
        {
            perror(strerror(errno)); 
            // ft_close_fd(pipefd);
            return;
        }
        if (pid == 0)
        {
            // if (in_fd != STDIN_FILENO)
            // {
            //     if (dup2(in_fd, STDIN_FILENO) == -1)
            //     {
            //         perror("dup2 stdin");
            //         exit(EXIT_FAILURE);
            //     }
            //     close(in_fd);
            // }
            // if (cmd->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
            // {
            //     perror("dup2 stdout");
            //     exit(EXIT_FAILURE);
            // }
            // ft_close_fd(pipefd);
            path_cmd = get_path(*env, cmd->arg[0]);
            if (!path_cmd)
            {
                fprintf(stderr, "command not found: %s\n", cmd->arg[0]);
                exit(EXIT_FAILURE);
            }
            // printf("0 : %s 1: %s 2: \n", cmd->arg[0], cmd->arg[1], cmd->arg[2]);
            execve(path_cmd, cmd->arg, put_env_in_ar(*env));
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, NULL, 0);
            close(pipefd[1]);
            in_fd = pipefd[0];
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

void	ft_init(t_exec *ex)
{
    ex->fd_in = STDIN_FILENO;
    ex->fd_out = STDOUT_FILENO;
    ex->error = 0;
}

void    ft_process(t_env **env, t_exec *ex)
{
	int 	command_nb;
	int		fd;
	int		pipefd[2];
	int		std_dup[2];
    t_exec  *current;

    ft_init(ex);
    current = ex;
	fd = 0;
	std_dup[0] = dup(STDIN_FILENO);
	std_dup[1] = dup(STDOUT_FILENO);
    // if (pipe(pipefd) == -1) //rm if no pipe, only if token pipe
	// {
    // 	perror("pipe failed");
    // 	exit(1);
	// }
    print_exec_args(ex);
    while (current)
    {
        if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT 
	    || current->type == TOKEN_REDIR_APPEND)
            ft_open(current, pipefd);
        current = current->next;
        printf("HERE\n");
    }
    printf("exiting\n");
    if (ex->error == 1)
    {
        // ft_close_fd(pipefd);
        return;
    }
	command_nb = count_command(ex);
	while (ex)
	{
    	if ((command_nb == 1) && (is_builtin(ex) == 1)) //redir avant, fo ft open parce que des fois y a des redir mdr
    	{
            printf("entering builtin exec\n");
			exec_builtin(ex, env);
            return ;
        }
		else
		{
			//ft_redir(ex);
			ex->fd_in = fd;
			ft_fork(ex, env, pipefd);
			dup2(std_dup[1], STDOUT_FILENO);
			dup2(std_dup[0], STDIN_FILENO);
			close(std_dup[0]);
			close(std_dup[1]);
		 	return ;
		}
		ex = ex->next;
	}
	while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? 
    {
    }
	// ft_close_fd(pipefd);
	return ;
}
    
