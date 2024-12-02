/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:41:37 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:06 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if ((siz == 0) || (siz <= len_dst))
		return (siz + len_src);
	while (dst[i] != '\0')
		i++;
	while ((src[j] != '\0') && (i + 1 < siz))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	int	i;

	i = ft_strlcat(av[1], av[2], 11);
	printf("%d\n", i);
	return (0);
}*/
