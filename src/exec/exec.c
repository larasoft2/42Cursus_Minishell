/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:11 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/03 17:48:17 by racoutte         ###   ########.fr       */
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

void	ft_exec(t_exec *ex, t_env **env)
{
	char	*path_cmd;
	char	**env_array;

	path_cmd = get_path(*env, ex->arg[0]);
	env_array = put_env_in_ar(*env);
	if (!path_cmd)
	{
		print_error_exec_message(COMMAND_NOT_FOUND, ex->arg[0]);
		ft_free_and_null(env_array);
		free_exec_list(&ex);
		free_env_list(env);
		exit(127);
	}
	execve(path_cmd, ex->arg, env_array);
	perror("execve");
	ft_free_and_null(env_array);
	free(path_cmd);
	free_exec_list(&ex);
	free_env_list(env);
	exit(EXIT_FAILURE);
}

void	ft_fork(t_exec *cmd, t_env **env, int *std_dup)
{
	int		status;
	pid_t	pid;

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
	while (wait(&status) > 0)
		continue ;
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

int	process_commands(t_exec *ex, t_env **env,
	int *std_dup, bool has_command)
{
	if (has_heredoc(ex) == 1 && g_signal != SIGINT) //added && from raph
		ft_open_heredocs(ex, ex->fd_in);
	if (!has_command && has_heredoc(ex) == 1 && g_signal != SIGINT) //added && from raph //has heredoc useless?
	{
		handle_redir(ex);
		dup2(std_dup[0], STDIN_FILENO);
		dup2(std_dup[1], STDOUT_FILENO);
	}
	else if (has_pipe(ex) == 1)
	{
		if (has_redir(ex) != 1)
			handle_pipes_no_redir(ex, env, std_dup);
		else
			handle_pipes_if_redir(ex, env, std_dup);
	}
	else if (has_pipe(ex) != 1)
	{
		if (handle_redir(ex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		exec_commands(ex, env, std_dup);
	}
	return (EXIT_SUCCESS);
}

void	ft_process(t_env **env, t_exec *ex)
{
	int		std_dup[2];
	bool	has_command;
	t_exec	*current;

	has_command = check_command_in_list(ex);
	ft_init(ex, std_dup);
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
