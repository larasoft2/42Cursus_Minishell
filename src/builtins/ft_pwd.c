/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:39 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/18 17:53:00 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd_out)
{
	char	dir[4096];

	if (getcwd(dir, 4096))
	{
		if (fd_out >= 0)
		{
			ft_putendl_fd(dir, fd_out);
			return (modify_value_exit_code(0), EXIT_SUCCESS);
		}
	}
	ft_putendl_fd("pwd: error retrieving current directory", 2);
	return (modify_value_exit_code(1), EXIT_FAILURE);
}
