/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:16 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/07 18:55:35 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HAS_N_OPTION 1
#define NO_N_OPTION 0

int	check_n_option(char *arg)
{
	size_t	i;

	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (HAS_N_OPTION);
		else
			return (NO_N_OPTION);
	}
	else
		return (NO_N_OPTION);
}


int	ft_echo(t_exec *ex)
{
	int	i;
	int	has_n_option;

	i = 1;
	has_n_option = 0;
	if (nbr_of_args(ex) < 2)
	{
		printf("\n");
		return (0);
	}
	if (check_n_option(ex->arg[1]) == HAS_N_OPTION)
	{
		has_n_option = 1;
		i++;
	}
	while (ex->arg[i])
	{
		printf("%s", ex->arg[i]);
		if (ex->arg[i + 1])
			printf(" ");
		i++;
	}
	if (!has_n_option)
		printf("\n");
	return (EXIT_SUCCESS);
}
