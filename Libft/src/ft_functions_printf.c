/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:56:19 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:40:19 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c, int count_final)
{
	write(1, &c, 1);
	count_final++;
	return (count_final);
}

int	ft_putstr_printf(char *str, int count_final)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		count_final++;
	}
	return (count_final);
}

int	ft_strlen_printf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count_number_length(long nbr, char *base, int count_final)
{
	int	len;

	len = ft_strlen_printf(base);
	if (nbr < 0)
		nbr = nbr * (-1);
	if (nbr == 0)
		count_final++;
	while (nbr > 0)
	{
		count_final++;
		nbr = nbr / len;
	}
	return (count_final);
}

int	ft_putnbr_base(long nbr, char *base, int count_final)
{
	int	len;

	len = ft_strlen_printf(base);
	count_final = count_number_length(nbr, base, count_final);
	if (nbr < 0)
	{
		ft_putchar_printf('-', count_final);
		nbr = nbr * (-1);
		count_final++;
	}
	if (nbr >= len)
	{
		ft_putnbr_base(nbr / len, base, count_final);
	}
	ft_putchar_printf(base[nbr % len], count_final);
	return (count_final);
}
