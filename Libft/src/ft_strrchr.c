/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:58:12 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:25 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	c = (char)c;
	str = (char *)s;
	len = ft_strlen(str);
	if (str[len - 1] == '\0' && c == '\0')
		return (&str[len - 1]);
	while (len >= 0)
	{
		if (str[len] == c)
			return (&str[len]);
		len--;
	}
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	char *str;

	str = ft_strrchr(av[1], 'H');
	printf("%c\n", *str);
	return (0);
}*/
