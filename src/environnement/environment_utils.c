/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:54:54 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/18 17:54:54 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	*ft_free_array(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return (NULL);
	while (ar[i])
		i++;
	while (i > 0)
		free(ar[--i]);
	free(ar);
	ar = NULL;
	return (NULL);
}
