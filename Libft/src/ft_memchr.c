/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:36:05 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:41:48 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	(void)ac;

	ft_memchr(av[1], 'l', 3);
	printf("%s\n", av[1]);
	return (0);
}*/
