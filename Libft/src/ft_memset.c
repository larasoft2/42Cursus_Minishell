/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:25:24 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:02 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	size_t nb;
	int	c;
	unsigned char str[6] = "Hello";

	nb = 5;
	c = 'a';
	printf("%s\n", str);
	ft_memset(str, c, nb);
	printf("%s\n", str);
	return (0);
}
*/
