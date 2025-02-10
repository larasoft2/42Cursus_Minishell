/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:24 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/10 17:45:15 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_len_one(int fd_out)
// {
// 	ft_putendl_fd("exit", fd_out);
// 	return (0);
// }

long	*get_exit_status(void)
{
	long	*exit_status;

	return (&exit_status);
}

static int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (EXIT_SUCCESS);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_exec *ex, int exit_status)
{
	//attention: il faut print exit ! 

	long	exit_code;
	int		len_cmd;

	len_cmd = nbr_of_args(ex);
	exit_code = 0;
	if (check_if_cmd_has_arg(ex->arg) == NO_ARGUMENTS)
	{
		//exit avec le dernier $?
	}
	if (len_cmd > 2)
	{
		print_error_exec_message(TOO_MANY_ARGUMENTS, ex->arg[0]);
		return (1) ; // seul cas ou on ne doit pas quitter le shell !!
	}
	if (!is_numeric(ex->arg[1]) || ft_atol(ex->arg[1]) > INT_MAX
		|| ft_atol(ex->arg[1]) < INT_MIN)
	{
		print_error_exec_message(NUMERIC_ARGUMENT_REQUIRED, ex->arg[1]);
		exit(2);
	}

	exit_code = ft_atol(ex->arg[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;

	return (exit_code);
}


