/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:05:45 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:31 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (s == NULL)
		dest = NULL;
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	dest = (char *) malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < start)
		i++;
	while (i < (start + len) && s[i])
	{
		dest[i - start] = s[i];
		i++;
	}
	dest[i - start] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*dest;
	char	src[30] = "Hello World and 42 School";

	dest = ft_substr(src, 6, 5);
	printf("%s\n", dest);
	return (0);
}*/
