/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/11 20:05:01 by lusavign         ###   ########.fr       */
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
        if (ex->fd_in != -1)
        {
            close(ex->fd_in);
            ex->fd_in = -1;
        }
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
        if (ex->fd_out != -1)
        {
            close(ex->fd_out);
            ex->fd_out = -1;
        }
    } 
    else
    {
        ex->fd_in = STDIN_FILENO;
        ex->fd_out = STDOUT_FILENO;
    }
}

void	open_redir_pipe(t_exec *ex)
{
    if (ex->type == TOKEN_REDIR_IN) 
    {
        ex->fd_in = open(ex->arg[0], O_RDONLY);
        if (ex->fd_in < 0) 
        {
            perror("Error opening input file");
            return;
        }
        // fprintf(stderr, "[DEBUG] Opened input file %s -> FD %d\n", ex->arg[0], ex->fd_in);
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
            return;
        }
        // fprintf(stderr, "[DEBUG] Opened output file %s -> FD %d\n", ex->arg[0], ex->fd_out);
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

void ft_fork(t_exec *cmd, t_env **env)
{
    pid_t   pid;
    int     status;
    
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
        cmd = cmd->next;
    }
    while (wait(&status) > 0);
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
		 	return ;
		}
		ex = ex->next;
	}
    ft_close_fd(std_dup);
}

void    handle_redir_in_pipe(t_exec *ex)
{
    t_exec  *current = ex;


    // fprintf(stderr, "in handle redir in pipe\n");
    while (current) 
    {
        // fprintf(stderr,"CMD IN HANDLE REDIR PIPE %s\n", current->arg[0]);

        if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT 
            || current->type == TOKEN_REDIR_APPEND)
        {
            // fprintf(stderr,"[DEBUG] Applying Redirection: TYPE %i CMD %s\n", current->type, current->arg[0]);
            ft_open(current, NULL);  // 🔹 Ouvrir mais pas `dup2()`
        }
        if (current->type == TOKEN_PIPE)
        {
            // fprintf(stderr,"[DEBUG] Found PIPE, resetting redirections.\n");
            current = current->next;
            break;
            // if (current)
                // fprintf(stderr,"[DEBUG] Moving to next command: %s\n", current->arg[0]);
        }
        else
            current = current->next;
    }
}

void    handle_pipes_no_redir(t_exec *ex, t_env **env)
{
    int         pipefd[2];
    int         fd_in;
    pid_t       pid;
    int         status;
    t_exec      *current;

    current = ex;
    fd_in = STDIN_FILENO;

    while (ex)
    {
        while (ex && (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_OUT 
        || ex->type == TOKEN_REDIR_APPEND))
                ex = ex->next;
        if (!ex || ex->type != TOKEN_WORD)
            break;
        if (ex->next && ex->next->type == TOKEN_PIPE) // si autre cmd suit, on crée un pipe
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
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // child
        {
            if (fd_in != STDIN_FILENO) // redirect stdin si nécessaire
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
                fd_in = -1;
            }
            if (pipefd[1] != -1) // redirect stdout > pipe
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (pipefd[0] != -1)
            {
                close(pipefd[0]);
                pipefd[0] = -1;
            }
            handle_redir(current, pipefd); //jsp si au bon endroit
            ft_exec(ex, env);
            exit(EXIT_FAILURE);
        }
        // parent
        if (fd_in != STDIN_FILENO)
        {
            close(fd_in); // close ancien fd_in
            fd_in = -1;
        }
        if (pipefd[1] != -1)
        {
            close(pipefd[1]); // close write end of pipe
            pipefd[1] = -1;
        }
        // prep fd_in next cmd
        fd_in = pipefd[0];
        ex = ex->next;
        if (ex && ex->type == TOKEN_PIPE)
            ex = ex->next;
    }
    while (wait(&status) > 0);
}

void handle_pipes_if_redir(t_exec *ex, t_env **env)
{
    int         pipefd[2];
    int         fd_in;
    // int         fd_out;
    pid_t       pid;
  //  int         status;
    t_exec      *current;
    t_exec      *block_begin;

    current = ex;
    block_begin = ex;
    fd_in = -1;
    // fd_out = dup(STDOUT_FILENO);
    while (current)
    {
        while (current && (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT 
        || current->type == TOKEN_REDIR_APPEND))
                current = current->next;
        if (!current || current->type != TOKEN_WORD)
            break;
        if (current->next && current->next->type == TOKEN_PIPE) // si autre cmd suit, on crée un pipe
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
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed"); //close fds
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // child
        {
            handle_redir_in_pipe(block_begin);
            ft_exec(current, env);
            exit(EXIT_FAILURE);
        }
        // parent
        if (fd_in != -1) //error here
        {
            close(fd_in);
            fd_in = -1;
        }
        if (pipefd[1] != -1)
        {
            close(pipefd[1]);
            pipefd[1] = -1;
        }
        fd_in = pipefd[0];
        while (current && current->type != TOKEN_PIPE)
            current = current->next;
        if (current && current->type == TOKEN_PIPE)
            current = current->next;
        block_begin = current;
    }
    for (int i = 0; i < 2; i++)
        wait(NULL);
    // while (wait(&status) > 0);
}

void    ft_process(t_env **env, t_exec *ex)
{
	int		    pipefd[2];
	int		    std_dup[2];

    ft_init(ex, std_dup);
    if (is_pipe(ex) == 1)
    {
        if (is_redir(ex) != 1)
            handle_pipes_no_redir(ex, env);
        else
            handle_pipes_if_redir(ex, env);
    }
    else if ((is_pipe(ex) != 1))
    {
        handle_redir(ex, pipefd);
        exec_commands(ex, env, std_dup);
    }
    ft_close_fd(std_dup);
	return ;
}
