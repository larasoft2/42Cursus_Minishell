/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:43 by lusavign          #+#    #+#             */
/*   Updated: 2025/03/04 23:41:57 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_heredocs(t_exec *ex, int pipefd)
{
	int		fd_in;
	t_exec	*current;

	fd_in = pipefd;
	current = ex;
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
				return ;
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

char	*generate_heredoc_name(char	*heredoc)
{
	int		i;
	char	*nb;
	char	*tmp;

	i = 0;
	heredoc = ft_strdup(".tmpheredoc");
	if (!heredoc)
		return (NULL);
	while (access(heredoc, F_OK) == 0)
	{
		free(heredoc);
		nb = ft_itoa(++i);
		if (!nb)
			return (NULL);
		tmp = ft_strjoin(".tmpheredoc", nb);
		free(nb);
		heredoc = tmp;
	}
	return (heredoc);
}

int	prepare_heredoc_file(t_exec *ex)
{
	int		tmp;
	char	*heredoc;

	heredoc = NULL;
	if (!ex || !ex->arg || !ex->arg[0])
	{
		perror("No delimiter in heredoc");
		return (-1);
	}
	heredoc = generate_heredoc_name(heredoc);
	if (!heredoc)
		return (-1);
	if (ex->hd_name)
		free(ex->hd_name);
	ex->hd_name = heredoc;
	tmp = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp < 0)
	{
		perror("Error opening heredoc\n");
		unlink(heredoc);
		return (-1);
	}
	return (tmp);
}

void	heredoc_loop(t_exec *ex, char *delimiter, int *tmp)
{
	char	*rline;

	rline = NULL;
	while (1)
	{
		if (g_signal == SIGINT)
			return (free(rline));
		rline = readline("> ");
		if (g_signal == SIGINT)
			return (free(rline));
		if (!rline)
		{
			print_delimiter_error_message(delimiter);
			*tmp = open(ex->hd_name, O_RDONLY);
			return ((void)close(*tmp));
		}
		if (!ft_strcmp(rline, delimiter))
		{
			free(rline);
			break ;
		}
		write(*tmp, rline, ft_strlen(rline));
		write(*tmp, "\n", 1);
		free(rline);
	}
}

int	handle_heredoc(t_exec *ex)
{
	int		tmp;
	char	*delimiter;

	if (!ex || !ex->arg || !ex->arg[0])
	{
		perror("No delimiter in heredoc");
		return (-1);
	}
	tmp = prepare_heredoc_file(ex);
	if (tmp < 0)
		return (-1);
	delimiter = ex->arg[0];
	setup_heredoc_signals_handling();
	heredoc_loop(ex, delimiter, &tmp);
	close(tmp);
	tmp = open(ex->hd_name, O_RDONLY);
	setup_default_signals_handling();
	return (tmp);
}
