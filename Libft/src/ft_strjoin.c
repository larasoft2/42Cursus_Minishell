/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:50:45 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:02 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*dest;

	size = ft_strlen(s1) + ft_strlen(s2);
	if (size == 0)
	{
		dest = (char *)malloc(sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	ft_strcat(dest, (char *)s2);
	return (dest);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	char	*str;
// 	int	size;

// 	(void)ac;
// 	size = 5;
// 	str = ft_strjoin(size, av, NULL);
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }
