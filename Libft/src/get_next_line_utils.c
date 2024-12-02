/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:25:43 by racoutte          #+#    #+#             */
/*   Updated: 2024/09/30 18:53:53 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str;

// 	i = 0;
// 	str = (unsigned char *)s;
// 	while (i < n)
// 	{
// 		str[i] = c;
// 		i++;
// 	}
// 	return (s);
// }

char	*ft_strcat_until_n(char *dest, char *src, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && src[j] != c)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (src[j] == c)
	{
		dest[i] = c;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
// {
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	len = ft_strlen(src);
// 	if (siz != 0)
// 	{
// 		while (src && src[i] && i < siz - 1)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (len);
// }

char	*ft_strjoin_line_stash(char *s1, char const *s2, char c)
{
	int		size;
	char	*dest;

	size = ft_strlen(s1) + (BUFFER_SIZE + 1);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	ft_strcat_until_n(dest, (char *)s2, c);
	free(s1);
	return (dest);
}
