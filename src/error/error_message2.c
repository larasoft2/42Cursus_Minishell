/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:24:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/05 21:23:05 by lusavign         ###   ########.fr       */
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

int	print_error(char *filename)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (EXIT_FAILURE);
}

void	append_to_message(char *msg, char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		msg[*len] = str[i];
		(*len)++;
		i++;
	}
}

void	print_command_not_found(char *command)
{
	int		len;
	char	msg[512];

	len = 0;
	append_to_message(msg, "minishell: ", &len);
	append_to_message(msg, command, &len);
	append_to_message(msg, ": command not found\n", &len);
	write(STDERR_FILENO, msg, len);
}

int	print_perm(char *command)
{
	int		len;
	char	msg[512];

	len = 0;
	append_to_message(msg, "minishell: ", &len);
	append_to_message(msg, command, &len);
	append_to_message(msg, ": Permission denied\n", &len);
	write(STDERR_FILENO, msg, len);
	return (EXIT_FAILURE);
}
