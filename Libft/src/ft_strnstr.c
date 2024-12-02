/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:44:56 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:21 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	if (ft_strlen(big) < ft_strlen(little) || len < ft_strlen(little))
		return (NULL);
	while (big[i])
	{
		j = 0;
		if (big[i] == little[j] && (i < len))
		{
			while ((big[i + j] == little[j]) && (little[j] != '\0'))
				j++;
			if (i + j > len)
				return (NULL);
			if ((little[j] == '\0') || j == len)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;

// 	// ft_strlen(NULL);
// 	str = ft_strnstr(NULL, "fake", 3);
// 	printf("%s\n", str);
// 	return (0);
// }
