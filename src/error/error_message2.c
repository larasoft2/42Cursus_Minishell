/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:24:09 by racoutte          #+#    #+#             */
/*   Updated: 2025/03/04 20:18:50 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *filename)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (EXIT_FAILURE);
}

void	print_command_not_found(char *command)
{
	int		i;
	int		len;
	char	msg[512];
	char	*msg_tail;


	len = 0;
	i = 0;
	while ("minishell: "[i] != '\0')
	{
		msg[len] = "minishell: "[i];
		len++;
		i++;
	}
	i = 0;
	while (command[i] != '\0')
	{
		msg[len] = command[i];
		len++;
		i++;
	}
	msg_tail = ": command not found\n";
	i = 0;
	while (msg_tail[i] != '\0')
	{
		msg[len] = msg_tail[i];
		len++;
		i++;
	}
	write(STDERR_FILENO, msg, len);
}
