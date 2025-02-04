/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:28 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/04 15:35:51 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export with no options;
// sets environment variables
//
// export can set a null variable that won't show in env
// but will show when typing export
// export alone shows all variables

// export	a = $b
// export b = $a must not loop

char	*extract_value(char *arg)
{
	size_t	i;
	size_t	len;
	char	*new_value;

	i = 0;
	len = ft_strlen(arg);
	while (arg[i] && arg[i] != "=")
		i++;
	new_value = (char *)malloc(sizeof(char) * (len - i + 2));
	if (!new_value)
		return (NULL);
	new_value = ft_substr(arg, i, len - i + 1);
	return (new_value);
}

void	modify_value(char *arg, t_env *env)
{
	
}


int	check_if_var_name_already_exists(char *arg, t_env *env)
{
	t_env	*temp;
	char	*new_value;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(arg, temp->key) == 0)
		{
			new_value = extract_value(arg);
			modify_value(arg, temp);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

int	check_if_var_name_is_valid(char *arg)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(arg[0]) || arg[0] != "_")
			return (EXIT_FAILURE);
	while (arg[i] && arg[i] != "=")
	{
		if (!ft_isalpha(arg[i]) || !ft_isdigit(arg[i]) || arg[i] != "_")
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_if_export_has_arg(char **arg)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (arg[i])
		count++;
	if (count == 1)
		return (NO_ARGUMENTS);
	else
		return (ARGUMENTS);
}

void	modify_env(t_exec *exec, t_env *env)
{

}

void	ft_export(t_exec *exec, t_env *env)
{
	t_exec *temp;

	temp = exec;
	if (check_if_export_has_arg(exec->arg) == NO_ARGUMENTS)
	{
		print_env(env);
		return ;
	}
	else
	{
		while (temp != NULL)
		{
			if (check_if_var_name_is_valid(exec->arg[1]) == EXIT_FAILURE)
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (NULL);
			}
			else
			{
				modify_env();
			}
			temp = temp->next;
		}
	}
}
