/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:46 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/21 17:41:27 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* protection si string vide??*/
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (i < n && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
	{
		if (s1)
			return (s1[0]);
		else
			return (-s2[0]);
	}
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

bool	check_command_in_list(t_exec *ex)
{
	t_exec	*current;

	current = ex;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			return (true);
		current = current->next;
	}
	return (false);
}

int	count_command(t_exec *ex)
{
	int	i;

	if (!ex)
		return (0);
	i = 0;
	while (ex)
	{
		if (ex->type == TOKEN_WORD)
			i++;
		ex = ex->next;
	}
	return (i);
}

int	nbr_of_args(t_exec *ex)
{
	int	i;

	if (!ex)
		return (0);
	i = 0;
	while (ex->arg[i])
		i++;
	return (i);
}
