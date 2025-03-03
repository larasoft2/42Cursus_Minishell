/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_no_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 23:52:26 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(int *pipefd, t_exec *ex)
{
	if (ex->next && ex->next->type == TOKEN_PIPE)
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
}

void	handle_child_io(int fd_in, int *pipefd)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		ft_close_fds(fd_in);
	}
	if (pipefd[1] != -1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		ft_close_fds(pipefd[1]);
	}
	if (pipefd[0] != -1)
		ft_close_fds(pipefd[0]);
}

void	execute_child_process(t_struct *data, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid > 0) //added from raph
		setup_command_mode_signals_handling();
	else if (pid == 0)
	{
		setup_command_mode_signals_handling(); //added from raph
		handle_child_io(data->fd_in, data->pipefd);
		handle_redir(data->current);
		ft_exec(data->current, env);
		exit(EXIT_FAILURE);
	}
}

void	handle_parent_io(int *fd_in, int *pipefd)
{
	if (*fd_in != STDIN_FILENO)
	{
		ft_close_fds(*fd_in);
		*fd_in = -1;
	}
	if (pipefd[1] != -1)
	{
		ft_close_fds(pipefd[1]);
		pipefd[1] = -1;
	}
	*fd_in = pipefd[0];
}

void	handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup)
{
	int			status;
	int			pipefd[2];
	t_struct	name;

	name.ex = ex;
	name.fd_in = STDIN_FILENO;
	ft_close_fd(std_dup);
	while (ex)
	{
		ex = find_next_valid_token(ex);
		if (!ex || ex->type != TOKEN_WORD)
			break ;
		name.current = ex;
		prepare_pipe(pipefd, ex);
		name.pipefd[0] = pipefd[0];
		name.pipefd[1] = pipefd[1];
		execute_child_process(&name, env);
		handle_parent_io(&name.fd_in, pipefd);
		ex = get_next_exec_token(ex);
	}
	while (wait(&status) > 0)
		continue ;
	ft_close_fd(pipefd);
}
