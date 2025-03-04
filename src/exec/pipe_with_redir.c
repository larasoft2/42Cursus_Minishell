/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/04 22:42:38 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_pipes *p, t_env **env)
{
	ft_close_fd(p->std_dup);
	if (p->fd_in != -1)
	{
		close(p->fd_in);
		p->fd_in = -1;
	}
	if (handle_redir_in_pipe(p->block_begin, p->fd_in) == EXIT_FAILURE)
	{
		free_env_list(env);
		free_exec_list(&p->begin);
		exit(EXIT_FAILURE);
	}
	ft_exec(p->current, env, NULL, NULL, p);
}

void	create_process(t_pipes *p, t_env **env, pid_t *pid)
{
	p->pid = fork();
	if (p->pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (p->pid > 0)
		setup_command_mode_signals_handling(); //added from raph
	if (p->pid == 0)
	{
		free(pid);
		setup_command_mode_signals_handling(); //added from raph
		child_process(p, env);
	}
}

void	clean_up_after_command(t_pipes *p)
{
	if (p->pipefd[1] != -1)
	{
		close(p->pipefd[1]);
		p->pipefd[1] = -1;
	}
	while (p->current && p->current->type != TOKEN_PIPE)
		p->current = p->current->next;
	if (p->current && p->current->type == TOKEN_PIPE)
		p->current = p->current->next;
	else if (p->fd_in != -1)
	{
		close(p->fd_in);
		p->fd_in = -1;
	}
	dup2(p->std_dup[0], STDIN_FILENO);
	dup2(p->std_dup[1], STDOUT_FILENO);
	p->block_begin = p->current;
}

void	handle_command_block(t_pipes *p, t_env **env, pid_t *pid)
{
	setup_io_for_command(p);
	create_process(p, env, pid);
	clean_up_after_command(p);
}

void	handle_pipes_if_redir(t_exec *ex, t_env **env, int *std_dup)
{
	int			i;
	int			status;
	pid_t		*pid;
	t_pipes		p;

	i = 0; //ft_init
	p.fd_in = -1;
	p.current = ex;
	p.block_begin = ex;
	p.begin = ex;
	p.std_dup[0] = std_dup[0];
	p.std_dup[1] = std_dup[1];
	pid = malloc(count_command(ex) * sizeof(pid_t));
	while (p.current)
	{
		skip_redirections(&p.current);
		p.has_command = check_command_in_block(p.block_begin, p.current);
		if (!p.has_command && p.current && p.current->type == TOKEN_PIPE)
		{
			handle_empty_pipe(&p);
			continue ;
		}
		if (!p.current || p.current->type != TOKEN_WORD)
			break ;
		handle_command_block(&p, env, pid);
		pid[i++] = p.pid;
	}
	i = 0;
	while (i < count_command(ex) && waitpid(pid[i++], &status, 0))
		continue ;
	modify_value_exit_code(status / 256);
	free(pid);
}
