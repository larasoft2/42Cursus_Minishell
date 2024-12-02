/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:54:26 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:43 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	c = (char)c;
	str = (char *)s;
	i = 0;
	if (str[i] == '\0' && c == '\0')
		return (&str[i]);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (str[i] == '\0' && c == '\0')
		return (&str[i]);
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	char *str;

	str = ft_strchr(av[1], '\0');
	printf("%c\n", *str);
	return (0);
}*/
