/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:24 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/18 11:32:29 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	*get_exit_status(void)
{
	static long	exit_status;

	return (&exit_status);
}

void	modify_value_exit_code(long code)
{
	long	*exit_status;

	exit_status = get_exit_status();
	*exit_status = code;
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
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

long	calculate_exit_code(long nb)
{
	long	exit_code;

	exit_code = 0;
	if (nb >= 0)
		exit_code = nb % 256;
	else
		exit_code = 256 - ((-nb) % 256);
	return (exit_code);
}

int	ft_exit(t_exec *ex, t_env *env) // ATTENTION FERMETURE FDS avant exit !!
{
	long	*exit_code;
	int		len_cmd;

	len_cmd = nbr_of_args(ex);
	exit_code = get_exit_status();
	printf("exit\n");
	(void)env;
	if (!ex->arg[1])
	{
		free_env_list(&env);
		free_exec_list(&ex);
		exit(*exit_code); //exit avec le dernier $?
	}
	if (is_numeric(ex->arg[1]) == EXIT_FAILURE || ft_atol(ex->arg[1]) > INT_MAX
		|| ft_atol(ex->arg[1]) < INT_MIN)
	{
		print_error_exec_message(NUMERIC_ARGUMENT_REQUIRED, ex->arg[1]);
		free_env_list(&env);
		free_exec_list(&ex);
		exit(2);
	}
	if (len_cmd > 2)
	{
		print_error_exec_message(TOO_MANY_ARGUMENTS, ex->arg[0]);
		return (modify_value_exit_code(1), EXIT_FAILURE);
	}
	*exit_code = calculate_exit_code(ft_atol(ex->arg[1]));
	modify_value_exit_code(*exit_code);
	free_env_list(&env);
	free_exec_list(&ex);
	exit(*exit_code);
}
