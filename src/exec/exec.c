/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 23:13:31 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execve will receive cmd path as first arg
// then options and args as second
// env as last
// ft_close_fd at the end
// 	// check errors, parsing???
// access F OK check infiles chez Jean pour que ca ne cree pas outfile si infile invalide
//error check useless

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
    exit(EXIT_FAILURE);
}

void ft_fork(t_exec *cmd, t_env **env, int *std_dup)
{
	pid_t   pid;
	int     status;

	while (cmd)
	{
		while (cmd && (cmd->type > 1))
			cmd = cmd->next;
		if (!cmd || cmd->type != TOKEN_WORD)
			break ;
		pid = fork();
		if (pid == -1)
			return (perror(strerror(errno)));
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

//pipe sans redir
// void    handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup)
// {
//     int         pipefd[2];
//     int         fd_in;
//     pid_t       pid;
//     int         status;
//     t_exec      *current;

//     current = ex;
//     fd_in = STDIN_FILENO;
//     ft_close_fd(std_dup);
//     while (ex)
//     {
//         while (ex && (ex->type > 1))
//             ex = ex->next;
//         if (!ex || ex->type != TOKEN_WORD)
//             break ;
//         if (ex->next && ex->next->type == TOKEN_PIPE)
//         {
//             if (pipe(pipefd) == -1)
//             {
//                 perror("pipe failed");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             pipefd[0] = -1;
//             pipefd[1] = -1;
//         }
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork failed");
//             exit(EXIT_FAILURE);
//         }
//         if (pid == 0) // child
//         {
//             if (fd_in != STDIN_FILENO)
//             {
//                 dup2(fd_in, STDIN_FILENO);
//                 ft_close_fds(fd_in);
//                 fd_in = -1;
//             }
//             if (pipefd[1] != -1)
//             {
//                 dup2(pipefd[1], STDOUT_FILENO);
//                 ft_close_fds(pipefd[1]);
//             }
//             if (pipefd[0] != -1)
//             {
//                 ft_close_fds(pipefd[0]);
//                 pipefd[0] = -1;
//             }
//             handle_redir(current);
//             ft_exec(ex, env);
//             exit(EXIT_FAILURE);
//         }
//         // parent
//         if (fd_in != STDIN_FILENO)
//         {
//             ft_close_fds(fd_in);
//             fd_in = -1;
//         }
//         if (pipefd[1] != -1)
//         {
//             ft_close_fds(pipefd[1]);
//             pipefd[1] = -1;
//         }
//         fd_in = pipefd[0];
//         ex = ex->next;
//         if (ex && ex->type == TOKEN_PIPE)
//             ex = ex->next;
//     }
//     while (wait(&status) > 0);
//     ft_close_fd(pipefd);
// }

//pipe avec redir
void	handle_pipes_if_redir(t_exec *ex, t_env **env, int *std_dup) 
{
	int			pipefd[2];
	int			status;
	int 		prev_pipe_fd = -1;
	int			temp_in;
    bool        has_command;
	pid_t		pid;
	t_exec		*current;
	t_exec		*block_begin;
    t_exec      *temp;

	current = ex;
	block_begin = ex;
	while (current)
	{
		while (current && (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_REDIR_APPEND || current->type == TOKEN_REDIR_HEREDOC))
				current = current->next;
		temp = block_begin;
		has_command = false;
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
			close(pipefd[1]);
			current = current->next;
			block_begin = current;
			continue;
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
		if (pid == 0) // child
		{
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
    bool        has_command;

    has_command = false;
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
    if (!has_command && has_heredoc(ex) == 1)
    {
        ft_open_heredocs(ex, ex->fd_in);
        handle_redir(ex);
        dup2(std_dup[0], STDIN_FILENO);
        dup2(std_dup[1], STDOUT_FILENO);
    }
    else if (has_pipe(ex) == 1)
    {
        if (has_redir(ex) != 1)
            handle_pipes_no_redir(ex, env, std_dup);
        else
        {
            if (has_heredoc(ex) == 1)
                ft_open_heredocs(ex, ex->fd_in);
            handle_pipes_if_redir(ex, env, std_dup);
        }
    }
    else if ((has_pipe(ex) != 1))
    {
        if (has_heredoc(ex) == 1)
            ft_open_heredocs(ex, ex->fd_in);
        handle_redir(ex);
        exec_commands(ex, env, std_dup);
    }
    ft_close_fds(std_dup[0]);
    ft_close_fds(std_dup[1]);
    current = ex; //pq j'ai mis ca
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
