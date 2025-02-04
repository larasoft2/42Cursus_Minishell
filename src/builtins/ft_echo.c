/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:16 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/31 19:35:57 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo, with option - n;
// outputs the arguments passed to it

/*
** ft_echo : built-in echo
** affiche les args separes par un espace
** si l'option -n est presente, pas de retour a la ligne
** Array : tableau d'arguments contenant commane et args
*/

int	ft_echo(t_exec *ex)
{
	int	i;
	int	has_n_option;

	has_n_option = 0;
	if (nbr_of_args(ex) < 2)
	{
		printf("\n");
		return (0);
	}
	has_n_option = ft_strncmp(ex->arg[1], "-n", 2) == 0; 
	if (has_n_option)
		i = 2;
	else
		i = 1;
	while (ex->arg[i])
	{
		printf("%s", ex->arg[i]);
		if (ex->arg[i + 1])
			printf(" ");
		i++;
	}
	if (!has_n_option)
		printf("\n");
	return (0);
}

// int	main(void)
// {
// 	t_exec	ex;
// 	char	*args[] = {"echo", "-n", "Hello,", "world!", NULL};

// 	ex.arg = args;
// 	printf("args passed: \"-n Hello, world!\"\n");
// 	ft_echo(&ex, STDOUT_FILENO);
// 	return (0);
// }
