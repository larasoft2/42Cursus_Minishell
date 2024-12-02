/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:15:07 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:43:15 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*s_dest;

	i = 0;
	s_dest = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s_dest)
		return (NULL);
	while (s[i])
	{
		s_dest[i] = f(i, s[i]);
		i++;
	}
	s_dest[i] = '\0';
	return (s_dest);
}

// char	ft_toupper_c(unsigned int a, char c)
// {
// 	(void)a;
// 	return (ft_toupper(c));
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*str;

// 	str = ft_strmapi(av[1], ft_toupper_c);
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }
