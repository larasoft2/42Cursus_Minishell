/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_no_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 00:17:17 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_ex_ctx *ex_ctx, t_env **env, pid_t *pid, int *i)
{
	pid[*i] = fork();
	if (pid[*i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid[*i] > 0)
		setup_command_mode_signals_handling();
	else if (pid[*i] == 0)
	{
		setup_command_mode_signals_handling();
		handle_child_io(ex_ctx->fd_in, ex_ctx->pipefd);
		handle_redir(ex_ctx->current);
		ft_exec(ex_ctx->current, env, pid, ex_ctx);
		exit(EXIT_FAILURE);
	}
	*i += 1;
}

void	execute_pipeline(t_exec *ex, t_env **env, int *pipefd, pid_t *pid)
{
	int			i;
	t_ex_ctx	ex_ctx;

	i = 0;
	init_ex_ctx(&ex_ctx, ex);
	while (ex)
	{
		ex = find_next_valid_token(ex);
		if (!ex || ex->type != TOKEN_WORD)
			break ;
		ex_ctx.current = ex;
		prepare_pipe(pipefd, ex);
		ex_ctx.pipefd[0] = pipefd[0];
		ex_ctx.pipefd[1] = pipefd[1];
		execute_child_process(&ex_ctx, env, pid, &i);
		handle_parent_io(&ex_ctx.fd_in, pipefd);
		ex = get_next_exec_token(ex);
	}
}

void	handle_pipes_no_redir(t_exec *ex, t_env **env, int *std_dup, int count)
{
	pid_t		*pid;
	int			i;
	int			status;
	int			pipefd[2];

	ft_close_fd(std_dup);
	pid = malloc(count * sizeof(pid_t));
	if (!pid)
		return ;
	execute_pipeline(ex, env, pipefd, pid);
	ft_close_fd(pipefd);
	i = 0;
	while (i < count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	modify_value_exit_code(status / 256);
	free(pid);
}
