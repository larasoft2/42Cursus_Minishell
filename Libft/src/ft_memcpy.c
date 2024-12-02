/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:38:34 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:41:55 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*s;
	unsigned char		*d;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char src[6] = "Hello";
	char dest[6] = "World";

	ft_memcpy(dest, src, 2);
	printf("%s\n", dest);
	return (0);
}*/
