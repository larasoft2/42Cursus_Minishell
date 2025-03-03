/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:20:44 by racoutte          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:59 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = n * (-1);
	}
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_writestr(char *str, long nb)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_size(nb);
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * (-1);
	}
	while (nb >= 0)
	{
		if (nb < 10)
		{
			str[len - i - 1] = nb + 48;
			str[len] = '\0';
			return (str);
		}
		str[len - i - 1] = nb % 10 + 48;
		nb = nb / 10;
		i++;
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;

	nb = n;
	str = (char *)malloc(sizeof(char) * (ft_size(nb) + 1));
	if (!str)
		return (NULL);
	ft_writestr(str, nb);
	return (str);
}

// int	main(void)
// {
// 	int	nb = 2147483647;
// 	char	*str;

// 	str = ft_itoa(nb);
// 	printf("%s\n", str);
// 	return (0);
// }
