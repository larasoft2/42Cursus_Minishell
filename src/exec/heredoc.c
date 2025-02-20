/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:43 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/20 16:21:15 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash-5.1$ << ls -l
// > ls
// bash: -l: command not found
// bash-5.1$ << ls omg
// > ls
// bash: omg: command not found
// bash-5.1$ << ls omg
// > ls omg
// > ls
// bash: omg: command not found

//unlink to remove file
//Si le fichier existe tu rajoutes 1 puis strjoin(name, atoi(I)s

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
	// free(tmp); ??
	return (heredoc);
}

int	handle_heredoc(t_exec *ex)
{
	int		tmp;
	char	*rline;
	char	*heredoc;
	char	*delimiter;

	tmp = 0;
	heredoc = NULL;
	if (!ex || !ex->arg || !ex->arg[0])
	{
		perror("No delimiter in heredoc");
		return (-1);
	}
	delimiter = ex->arg[0];
	heredoc = generate_heredoc_name(heredoc);
	ex->hd_name = heredoc;
	tmp = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp < 0)
	{
		perror("Error opening heredoc\n");
		unlink(heredoc);
		return (-1);
	}
	setup_heredoc_signals_handling();
	while (1)
	{
		if (g_signal == SIGINT)
			break ;
		rline = readline("> ");
		if (g_signal == SIGINT)
			break ;
		if (!rline)
		{
			//free(heredoc);
			print_delimiter_error_message(delimiter);
			break;
		}
		if (!ft_strcmp(rline, delimiter))
		{
			free(rline);
			break;
		}
		write (tmp, rline, ft_strlen(rline));
		write (tmp, "\n", 1);
		free(rline);
	}
	close(tmp);
	tmp = open(heredoc, O_RDONLY);
	g_signal = 0;
	setup_default_signals_handling();
	return (tmp);
}
