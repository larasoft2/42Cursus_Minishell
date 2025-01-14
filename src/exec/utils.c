/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:46 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/14 21:23:46 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int *pipefd)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

char	*ft_strndup(const char *s, size_t n) // protection si string vide??
{
	size_t i;
	char *dest;

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

int	count_command(t_exec *ex)
{
	int	i;

	if (!ex)
		return (0);
	i = 0;
	while (ex)
	{
		if (ex->type && ex->type->type == TOKEN_WORD)
			i++;
		ex = ex->next;
	}
	printf("COMMAND COUNT: %i\n", i);
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
