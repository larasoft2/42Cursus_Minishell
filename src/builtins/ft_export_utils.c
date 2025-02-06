/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:57 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/06 16:01:05 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_var_name_is_valid(char *arg)
{
	size_t	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
			return (EXIT_FAILURE);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*extract_key_name(char *arg)
{
	size_t	key_len;
	char	*key;

	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	key = ft_substr(arg, 0, key_len);
	return (key);
}

char	*extract_var_value(char *arg)
{
	size_t	i;
	size_t	len;
	char	*new_value;

	i = 0;
	len = ft_strlen(arg);
	new_value = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (ft_strdup(""));
	new_value = ft_substr(arg, i + 1, len - i - 1);
	return (new_value);
}

void	modify_value(char *new_value, t_env *env_var)
{
	free(env_var->value);
	env_var->value = ft_strdup(new_value);
	if (!env_var->value)
		perror("Failed to allocate memory for new value");
}
