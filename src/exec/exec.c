/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/05 21:00:03 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_exec *ex, t_env **env, pid_t *pid, t_ex_ctx *ex_ctx)
{
	char	*path_cmd;
	char	**env_array;

	path_cmd = get_path(*env, ex->arg[0], ex);
	env_array = put_env_in_ar(*env);
	if (!path_cmd)
	{
		print_command_not_found(ex->arg[0]);
		ft_free_and_null(env_array);
		if (ex_ctx)
			free_exec_list(&ex_ctx->begin);
		else
			free_exec_list(&ex);
		free_env_list(env);
		if (pid)
			free(pid);
		exit(127);
	}
	execve(path_cmd, ex->arg, env_array);
	perror("execve");
	ft_free_and_null(env_array);
	if (path_cmd)
		free(path_cmd);
	if (ex_ctx)
		free_exec_list(&ex_ctx->begin);
	else
		free_exec_list(&ex);
	free_env_list(env);
	if (pid)
		free(pid);
	exit(EXIT_FAILURE);
}

void	ft_fork(t_exec *cmd, t_env **env, int *std_dup)
{
	int		status;
	pid_t	pid;

	while (cmd)
	{
		skip_redirections(&cmd);
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
			ft_exec(cmd, env, NULL, NULL);
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		continue ;
	get_exit_code(status);
}

void	exec_commands(t_exec *ex, t_env **env, int *std_dup)
{
	int		command_nb;

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

int	process_commands(t_exec *ex, t_env **env, int *std_dup, bool has_command)
{
	if (starting_hd(ex, std_dup) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (!has_command && has_heredoc(ex) == 1)
	{
		handle_redir(ex);
		dup2(std_dup[0], STDIN_FILENO);
		dup2(std_dup[1], STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (has_pipe(ex) == 1)
	{
		if (has_redir(ex) == 1)
			handle_pipes_if_redir(ex, env, std_dup);
		else
			handle_pipes_no_redir(ex, env, std_dup, count_command(ex));
		return (EXIT_SUCCESS);
	}
	if (handle_redir(ex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec_commands(ex, env, std_dup);
	return (EXIT_SUCCESS);
}

void	ft_process(t_env **env, t_exec *ex)
{
	int		std_dup[2];
	bool	has_command;
	t_exec	*current;

	has_command = check_command_in_list(ex);
	init_fd_dup(ex, std_dup);
	process_commands(ex, env, std_dup, has_command);
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
	return ;
}
