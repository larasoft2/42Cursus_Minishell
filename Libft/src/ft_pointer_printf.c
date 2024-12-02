/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:17:55 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:06 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_number_length_p(unsigned long long nbr, char *base, int count_final)
{
	int	len;

	len = ft_strlen_printf(base);
	if (nbr == 0)
		count_final++;
	while (nbr > 0)
	{
		count_final++;
		nbr = nbr / len;
	}
	return (count_final);
}

int	ft_putnbr_base_long(unsigned long long nbr, char *base, int count_final)
{
	unsigned int	len;

	len = ft_strlen_printf(base);
	count_final = count_number_length_p(nbr, base, count_final);
	if (nbr >= len)
	{
		ft_putnbr_base_long(nbr / len, base, count_final);
	}
	ft_putchar_printf(base[nbr % len], count_final);
	return (count_final);
}

int	ft_pointer(unsigned long long ptr, int count)
{
	if (!ptr)
		count = ft_putstr_printf("(nil)", count);
	else
	{
		count = ft_putstr_printf("0x", count);
		count = ft_putnbr_base_long(ptr, HEXALOW, count);
	}
	return (count);
}
