/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:43 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 16:27:10 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_delimiter_error_message(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	if (delimiter != NULL)
		ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
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

	while (1)
	{
		if (g_signal == SIGINT)
			break ;
		rline = readline("> ");
		if (g_signal == SIGINT)
			break ;
		if (!rline)
		{
			print_delimiter_error_message(delimiter);
			close(*tmp);
			*tmp = open(ex->hd_name, O_RDONLY);
			return ;
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
