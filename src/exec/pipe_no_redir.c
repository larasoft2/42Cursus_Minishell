/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_no_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/04 13:12:57 by lusavign         ###   ########.fr       */
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

void	execute_child_process(t_struct *data, t_env **env, pid_t *pid, int *i)
{
	pid[*i] = fork();
	if (pid[*i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid[*i] > 0) //added from raph
		setup_command_mode_signals_handling();
	else if (pid[*i] == 0)
	{
		setup_command_mode_signals_handling(); //added from raph
		handle_child_io(data->fd_in, data->pipefd);
		handle_redir(data->current);
		ft_exec(data->current, env);
		exit(EXIT_FAILURE);
	}
	*i += 1;
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

void	handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup, int count)
{
	int			i;
	int			status;
	int			pipefd[2];
	pid_t		*pid;
	t_struct	name;

	i = 0;
	pid = malloc(count * sizeof(pid_t));
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
		execute_child_process(&name, env, pid, &i);
		handle_parent_io(&name.fd_in, pipefd);
		ex = get_next_exec_token(ex);
	}
	i = 0;
	while (i < count)
		waitpid(pid[i++], &status, 0);
	ft_close_fd(pipefd);
	free(pid);
	modify_value_exit_code(status / 256);
}
