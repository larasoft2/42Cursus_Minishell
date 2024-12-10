/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:16 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/10 18:55:17 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

/*
** ft_echo : built-in echo
** affiche les args separes par un espace
** si l'option -n est presente, pas de retour a la ligne
** Array : tableau d'arguments contenant commane et args
*/

int	ft_echo(char **array, int fd_out)
{
	int	i;
	int	has_n_option;

	has_n_option = 0;
	if (nbr_of_args(array) < 2)
	{
		ft_putchar_fd('\n', fd_out);
		return (0);
	}
	if (ft_strncmp(array[1], "-n", 2) == 0)
	{
		has_n_option = 1;
		i = 2;
	}
	else
		i = 1;
	while (array[i])
	{
		ft_putstr_fd(array[i], fd_out);
		if (array[i + 1])
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (!has_n_option)
		ft_putchar_fd('\n', fd_out);
	return (0);
}
