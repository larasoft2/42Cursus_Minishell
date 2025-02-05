/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/05 14:54:47 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// execve will receive cmd path as first arg
// then options and args as second
// env as last
// ft_close_fd at the end


// 	// check errors, parsing???

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

// access F OK check infiles chez Jean pour que ca ne cree pas outfile si infile invalide
//error check useless

void	ft_open(t_exec *ex, int *pipefd)
{
    (void)pipefd; //do something with this
    if (ex->type == TOKEN_REDIR_IN) 
    {
        ex->fd_in = open(ex->arg[0], O_RDONLY);
        if (ex->fd_in < 0) 
        {
            perror("Error opening input file");
            //ft_close_fd(pipefd);
            return;
        }
        dup2(ex->fd_in, STDIN_FILENO);
        close(ex->fd_in);
    } 
    else if (ex->type == TOKEN_REDIR_OUT || ex->type == TOKEN_REDIR_APPEND) 
    {
        if (ex->type == TOKEN_REDIR_OUT)
            ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else if (ex->type == TOKEN_REDIR_APPEND)
            ex->fd_out = open(ex->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (ex->fd_out < 0)
        {
            perror("Error opening output file");
            // ft_close_fd(pipefd);
            return;
        }
        dup2(ex->fd_out, STDOUT_FILENO);
        close(ex->fd_out);
    } 
    else //idk if useful
    {
        ex->fd_in = STDIN_FILENO;
        ex->fd_out = STDOUT_FILENO;
    }
}

void    ft_exec(t_exec *ex, t_env **env)
{
    char *path_cmd;
    
    path_cmd = get_path(*env, ex->arg[0]);
    if (!path_cmd)
    {
        fprintf(stderr, "command not found: %s\n", ex->arg[0]);
        exit(EXIT_FAILURE); //free
    }
    execve(path_cmd, ex->arg, put_env_in_ar(*env));
    perror("execve");
    exit(EXIT_FAILURE); //pq exit failure

}
int child_count = 0;

void ft_fork(t_exec *cmd, t_env **env)
{
    pid_t pid;
    
    while (cmd)
    {
        while (cmd && (cmd->type == TOKEN_REDIR_IN || cmd->type == TOKEN_REDIR_OUT 
            || cmd->type == TOKEN_REDIR_APPEND || cmd->type == TOKEN_PIPE))
            cmd = cmd->next;
        if (!cmd || cmd->type != TOKEN_WORD)
            break;
        pid = fork();
        if (pid == -1)
        {
            perror(strerror(errno)); 
            return;
        }
        if (pid == 0)
            ft_exec(cmd, env);
        else
            child_count++;
        cmd = cmd->next;
    }
}

void    handle_redir(t_exec *ex, int *pipefd)
{
    t_exec  *current;

    current = ex;
    while (current)
    {
        if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT 
	    || current->type == TOKEN_REDIR_APPEND)
            ft_open(current, pipefd);
        current = current->next;
    }
}

void    exec_commands(t_exec *ex, t_env **env, int *std_dup)
{
    int     fd;
    int 	command_nb;

    fd = 0; //useless
    command_nb = count_command(ex);
    while (ex)
	{
    	if ((command_nb == 1) && (is_builtin(ex) == 1))
    	{
			exec_builtin(ex, env);
            restore_fds(std_dup);
            return ;
        }
		else
		{
			ex->fd_in = fd; // = stdin_fileno
			ft_fork(ex, env);
            restore_fds(std_dup);
            for (int i = 0; i < child_count; i++)
                wait(NULL); // LES FDS SONT NIQUES SA MERE!!!!!!!!!! 
		 	return ;
		}
		ex = ex->next;
	}
}

void handle_pipes(t_exec *ex, t_env **env)
{
    int pipefd[2];
    int fd_in = STDIN_FILENO; // Start with standard input

    while (ex)
    {
        if (ex->next && ex->next->type == TOKEN_PIPE) // Create a pipe if another command follows
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            pipefd[0] = -1;
            pipefd[1] = -1;
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // Child process
        {
            if (fd_in != STDIN_FILENO) // Redirect input if needed
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            if (pipefd[1] != -1) // Redirect output if needed
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            close(pipefd[0]); // Close unused read end
            ft_exec(ex, env);
            exit(EXIT_FAILURE);
        }
        // Parent process: close used pipes and update fd_in
        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (pipefd[1] != -1)
            close(pipefd[1]);
        fd_in = pipefd[0]; // Update fd_in for the next command
        ex = ex->next; // Move to the next command
        if (ex && ex->type == TOKEN_PIPE)
            ex = ex->next;
    }
    while (wait(NULL) > 0); // Wait for all children
}

void    ft_process(t_env **env, t_exec *ex)
{
	int		pipefd[2];
	int		std_dup[2];

    ft_init(ex, std_dup);
    if (is_pipe(ex) == 1)
        handle_pipes(ex, env);
    handle_redir(ex, pipefd);
    exec_commands(ex, env, std_dup);
	// while (wait(NULL) > 0) //if no child, return (-1), else return id //need to wait last cmd? it might not work
    // {
    // }
	// clean free
	return ;
}
