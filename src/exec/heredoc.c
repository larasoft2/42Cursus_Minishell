/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:43 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/13 18:33:21 by lusavign         ###   ########.fr       */
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

char	*generate_heredoc_name(char	*heredoc)
{	
	int		i;
	char	*num;
	char	*tmp;

	i = 0;
	heredoc = strdup("tmpheredoc");
	if (!heredoc)
		return (NULL);
	while (access(heredoc, F_OK) == 0)
	{
		free(heredoc);
		num = ft_itoa(++i);
		if (!num)
			return (NULL);
		tmp = ft_strjoin("tmpheredoc", num);
		free(num);
		heredoc = tmp;
	}
	return (heredoc);
}

void    handle_heredoc(t_exec *ex)
{
	char	*heredoc;
	int		tmp;

	heredoc = NULL;
	if (ex && ex->type == TOKEN_REDIR_HEREDOC)
	{	
		heredoc = generate_heredoc_name(heredoc);
		while (1)
		{
			tmp = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
			heredoc = readline("> ");
			//delimiter = ex->next->arg[0];
			//fprintf(stderr, "delimiter is %s", delimiter);
		}
	}
}
