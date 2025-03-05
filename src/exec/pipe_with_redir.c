/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_with_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:44:07 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 17:50:50 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_ex_ctx *ctx, t_env **env)
{
	ft_close_fd(ctx->std_dup);
	if (ctx->fd_in != -1)
	{
		close(ctx->fd_in);
		ctx->fd_in = -1;
	}
	if (handle_redir_in_pipe(ctx->block_begin, ctx->fd_in) == EXIT_FAILURE)
	{
		free_env_list(env);
		free_exec_list(&ctx->begin);
		exit(EXIT_FAILURE);
	}
	ft_exec(ctx->current, env, NULL, ctx);
}

void	create_process(t_ex_ctx *ex_ctx, t_env **env, pid_t *pid)
{
	ex_ctx->pid = fork();
	if (ex_ctx->pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (ex_ctx->pid > 0)
		setup_command_mode_signals_handling();
	if (ex_ctx->pid == 0)
	{
		free(pid);
		setup_command_mode_signals_handling();
		child_process(ex_ctx, env);
	}
}

void	clean_up_after_command(t_ex_ctx *ex_ctx)
{
	if (ex_ctx->pipefd[1] != -1)
	{
		close(ex_ctx->pipefd[1]);
		ex_ctx->pipefd[1] = -1;
	}
	while (ex_ctx->current && ex_ctx->current->type != TOKEN_PIPE)
		ex_ctx->current = ex_ctx->current->next;
	if (ex_ctx->current && ex_ctx->current->type == TOKEN_PIPE)
		ex_ctx->current = ex_ctx->current->next;
	else if (ex_ctx->fd_in != -1)
	{
		close(ex_ctx->fd_in);
		ex_ctx->fd_in = -1;
	}
	dup2(ex_ctx->std_dup[0], STDIN_FILENO);
	dup2(ex_ctx->std_dup[1], STDOUT_FILENO);
	ex_ctx->block_begin = ex_ctx->current;
}

void	handle_command_block(t_ex_ctx *ex_ctx, t_env **env, pid_t *pid)
{
	setup_io_for_command(ex_ctx);
	create_process(ex_ctx, env, pid);
	clean_up_after_command(ex_ctx);
}

void	handle_pipes_if_redir(t_exec *ex, t_env **env, int *std_dup)
{
	int			i;
	int			status;
	pid_t		*pid;
	t_ex_ctx	ctx;

	i = 0;
	init_ex_ctx_for_redir(&ctx, ex, std_dup);
	pid = malloc(count_command(ex) * sizeof(pid_t));
	while (ctx.current)
	{
		skip_redirections(&ctx.current);
		ctx.has_command = check_cmd_in_block(ctx.block_begin, ctx.current);
		if (!ctx.has_command && ctx.current && ctx.current->type == TOKEN_PIPE)
			handle_empty_pipe(&ctx);
		if (!ctx.current || ctx.current->type != TOKEN_WORD)
			break ;
		handle_command_block(&ctx, env, pid);
		pid[i++] = ctx.pid;
	}
	i = 0;
	while (i < count_command(ex) && waitpid(pid[i++], &status, 0))
		continue ;
	modify_value_exit_code(status / 256);
	free(pid);
}
