/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 16:48:35 by racoutte         ###   ########.fr       */
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

void	ft_close_fds(int fd)
{
	if (fd > 2)
		close(fd);
}

void	ft_open(t_exec *ex, int *fd_in)
{
    if (ex->type == TOKEN_REDIR_IN)
    {
        if (*fd_in > 2)
            ft_close_fds(*fd_in);
        *fd_in = open(ex->arg[0], O_RDONLY);
        if (*fd_in < 0)
        {
            perror("Error opening input file");
            return;
        }
    }
	else if (ex->type == TOKEN_REDIR_HEREDOC && g_signal != SIGINT)
	{
		if (*fd_in > 2)
			ft_close_fds(*fd_in);
		*fd_in = open(ex->hd_name, O_RDONLY);
		if (*fd_in < 0)
		{
			perror("Error opening heredoc file");
			return;
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
            return;
        }
        dup2(ex->fd_out, STDOUT_FILENO);
        if (ex->fd_out != -1)
        {
            ft_close_fds(ex->fd_out);
            ex->fd_out = -1;
        }
    }
    else
    {
        *fd_in = STDIN_FILENO;
        ex->fd_out = STDOUT_FILENO;
    }
}

void    ft_exec(t_exec *ex, t_env **env)
{
    char *path_cmd;
	char	**env_array;

	path_cmd = get_path(*env, ex->arg[0]);
	env_array = put_env_in_ar(*env);
    if (!path_cmd)
    {
		print_error_exec_message(COMMAND_NOT_FOUND, ex->arg[0]);
		ft_free_and_null(env_array);
		free_exec_list(&ex);
		free_env_list(env);
        exit(EXIT_FAILURE);
    }
    execve(path_cmd, ex->arg, env_array);
    perror("execve");
	ft_free_and_null(env_array);
	free(path_cmd);
	free_exec_list(&ex);
	free_env_list(env);
    exit(EXIT_FAILURE);
}

void ft_fork(t_exec *cmd, t_env **env, int *std_dup)
{
    pid_t   pid;
    int     status;

    while (cmd)
    {
        while (cmd && (cmd->type == TOKEN_REDIR_IN || cmd->type == TOKEN_REDIR_OUT
            || cmd->type == TOKEN_REDIR_APPEND || cmd->type == TOKEN_PIPE || cmd->type == TOKEN_REDIR_HEREDOC))
            cmd = cmd->next;
        if (!cmd || cmd->type != TOKEN_WORD)
            break;
        pid = fork();
        if (pid == -1)
        {
            perror(strerror(errno));
            return;
        }
		if (pid > 0)
			setup_command_mode_signals_handling();
        if (pid == 0)
        {
			setup_command_mode_signals_handling();
            ft_close_fd(std_dup);
            ft_exec(cmd, env);
        }
        cmd = cmd->next;
    }
    while (wait(&status) > 0); //waipitd?
}

void    handle_redir(t_exec *ex)
{
    t_exec  *current;
	int		fd_in;

	fd_in = 0;
    current = ex;
    while (current)
    {
        if (current->type > 1)
            ft_open(current, &fd_in);
        current = current->next;
    }
	if (fd_in > 2)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
}

void    exec_commands(t_exec *ex, t_env **env, int *std_dup)
{
    int 	command_nb;

    command_nb = count_command(ex);
    while (ex)
	{
    	if ((command_nb == 1) && (is_builtin(ex) == 1))
    	{
			exec_builtin(ex, env, std_dup);
            restore_fds(std_dup);
            return ;
        }
		else
		{
			ex->fd_in = STDIN_FILENO;
			ft_fork(ex, env, std_dup);
            restore_fds(std_dup);
		 	return ;
		}
		ex = ex->next;
	}
}

void    handle_redir_in_pipe(t_exec *ex, int pipefd)
{
    t_exec  *current = ex;
	int		fd_in;

	fd_in = pipefd;
	while (current)
    {
        if (current->type > 1)
            ft_open(current, &fd_in);
        if (current->type == TOKEN_PIPE)
            break;
        else
            current = current->next;
    }
	if (fd_in > 2)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
}

void    handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup)
{
    int         pipefd[2];
    int         fd_in;
    pid_t       pid;
    int         status;
    t_exec      *current;

    current = ex;
    fd_in = STDIN_FILENO;
    ft_close_fd(std_dup);
    while (ex)
    {
        while (ex && (ex->type == TOKEN_REDIR_IN || ex->type == TOKEN_REDIR_OUT
        || ex->type == TOKEN_REDIR_APPEND || ex->type == TOKEN_REDIR_HEREDOC))
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
        if (pid > 0)
			setup_command_mode_signals_handling();
		if (pid == 0) // child
		{
			setup_command_mode_signals_handling();
            if (fd_in != STDIN_FILENO)
            {
                dup2(fd_in, STDIN_FILENO);
                ft_close_fds(fd_in);
                fd_in = -1;
            }
            if (pipefd[1] != -1)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                ft_close_fds(pipefd[1]);
            }
            if (pipefd[0] != -1)
            {
                ft_close_fds(pipefd[0]);
                pipefd[0] = -1;
            }
            handle_redir(current);
            ft_exec(ex, env);
            exit(EXIT_FAILURE);
        }
        // parent
        if (fd_in != STDIN_FILENO)
        {
            ft_close_fds(fd_in);
            fd_in = -1;
        }
        if (pipefd[1] != -1)
        {
            ft_close_fds(pipefd[1]);
            pipefd[1] = -1;
        }
        fd_in = pipefd[0];
        ex = ex->next;
        if (ex && ex->type == TOKEN_PIPE)
            ex = ex->next;
    }
    while (wait(&status) > 0);
    ft_close_fd(pipefd);
}

void    ft_open_heredocs(t_exec *ex, int pipefd)
{
    t_exec  *current = ex;
    int     fd_in;

    fd_in = pipefd;
    while (current)
    {
        if (current->type == TOKEN_REDIR_HEREDOC && g_signal != SIGINT)
        {
            if (fd_in > 2)
                ft_close_fds(fd_in);
            fd_in = handle_heredoc(current);
            if (fd_in < 0)
            {
                perror("Error handling heredoc");
                return;
            }
        }
        current = current->next;
    }
    if (fd_in > 2)
    {
        dup2(fd_in, STDIN_FILENO);
        ft_close_fds(fd_in);
    }
}

void	handle_pipes_if_redir(t_exec *ex, t_env **env, int *std_dup)
{
	int			pipefd[2];
	int			status;
	int 		prev_pipe_fd = -1;
	int			temp_in;
	pid_t		pid;
	t_exec		*current;
	t_exec		*block_begin;

	current = ex;
	block_begin = ex;
	while (current)
	{
		while (current && (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_REDIR_APPEND || current->type == TOKEN_REDIR_HEREDOC))
				current = current->next;
		t_exec *temp = block_begin;
		bool has_command = false;
		while (temp && temp != current)
		{
			if (temp->type == TOKEN_WORD)
			{
				has_command = true;
				break;
			}
			temp = temp->next;
		}

		if (!has_command && current && current->type == TOKEN_PIPE)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe failed");
				exit(EXIT_FAILURE);
			}
			prev_pipe_fd = pipefd[0];
			close(pipefd[1]);  // Close the write end since we're not writing
			current = current->next; // Move past the pipe
			block_begin = current;   // Start a new block
			continue;                // Skip the rest of the loop
		}
		if (!current || current->type != TOKEN_WORD)
			break;
		temp_in = prev_pipe_fd;
		if (prev_pipe_fd != -1)
		{
			dup2(prev_pipe_fd, STDIN_FILENO);
			close(prev_pipe_fd);
			prev_pipe_fd = -1;
		}
		if (has_pipe(current) != -1) // si autre cmd suit, on crée un pipe
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe failed");
				exit(EXIT_FAILURE);
			}
			prev_pipe_fd = pipefd[0];
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		if (pipefd[1] != -1) // redirect stdout > pipe
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			pipefd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed"); //close fds
			exit(EXIT_FAILURE);
		}
		if (pid > 0)
			setup_command_mode_signals_handling();
		if (pid == 0) // child
		{
			setup_command_mode_signals_handling();
			ft_close_fd(std_dup);
			if (prev_pipe_fd != -1)
			{
				close(prev_pipe_fd);
				prev_pipe_fd = -1;
			}
			handle_redir_in_pipe(block_begin, temp_in);
			ft_exec(current, env);
			exit(EXIT_FAILURE);
		}
		if (pipefd[1] != -1)
		{
			close(pipefd[1]);
			pipefd[1] = -1;
		}
		while (current && current->type != TOKEN_PIPE)
			current = current->next;
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
		else
		{
			if (prev_pipe_fd != -1)
			{
				close(prev_pipe_fd);
				prev_pipe_fd = -1;
			}
		}
		dup2(std_dup[0], STDIN_FILENO);
		dup2(std_dup[1], STDOUT_FILENO);
		block_begin = current;
	}
	while (wait(&status) > 0); //waitpid
}

void ft_process(t_env **env, t_exec *ex)
{
    int         std_dup[2];
    t_exec      *current = ex;
    bool        has_command = false;

    // Check if there are any actual commands
    current = ex;
    while (current)
    {
        if (current->type == TOKEN_WORD)
        {
            has_command = true;
            break;
        }
        current = current->next;
    }

    ft_init(ex, std_dup);

    // If no command but has heredoc, treat like 'cat'
    if (!has_command && has_heredoc(ex) == 1 && g_signal != SIGINT)
    {
        ft_open_heredocs(ex, ex->fd_in);
        handle_redir(ex);
        // If no command specified with heredoc, read from stdin and write to stdout
        dup2(std_dup[0], STDIN_FILENO);
        dup2(std_dup[1], STDOUT_FILENO);
    }
    else if (has_pipe(ex) == 1)
    {
        // Rest of your existing code...
        if (has_redir(ex) != 1)
            handle_pipes_no_redir(ex, env, std_dup);
        else
        {
            if (has_heredoc(ex) == 1 && g_signal != SIGINT)
                ft_open_heredocs(ex, ex->fd_in);
            handle_pipes_if_redir(ex, env, std_dup);
        }
    }
    else if ((has_pipe(ex) != 1))
    {
        if (has_heredoc(ex) == 1 && g_signal != SIGINT)
            ft_open_heredocs(ex, ex->fd_in);
        handle_redir(ex);
        exec_commands(ex, env, std_dup);
    }

    // Clean up heredoc temporary files
    ft_close_fds(std_dup[0]);
    ft_close_fds(std_dup[1]);
    current = ex;
    while (current)
    {
        if (current->hd_name)
        {
            unlink(current->hd_name);
            free(current->hd_name);
            current->hd_name = NULL;
        }
        current = current->next;
    }
    return;
}
