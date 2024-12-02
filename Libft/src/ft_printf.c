/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:31:20 by racoutte          #+#    #+#             */
/*   Updated: 2024/09/02 17:50:43 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_list_conditions(const char *format, va_list ap, int count)
{
	if (*format == 'c')
		count = ft_putchar_printf(va_arg(ap, int), count);
	else if (*format == 's')
		count = ft_putstr_printf(va_arg(ap, char *), count);
	else if (*format == 'p')
		count = ft_pointer(va_arg(ap, unsigned long long), count);
	else if (*format == 'd')
		count = ft_putnbr_base(va_arg(ap, int), BASE10, count);
	else if (*format == 'i')
		count = ft_putnbr_base(va_arg(ap, int), BASE10, count);
	else if (*format == 'u')
		count = ft_putnbr_base(va_arg(ap, unsigned int), BASE10, count);
	else if (*format == 'x')
		count = ft_putnbr_base(va_arg(ap, unsigned int), HEXALOW, count);
	else if (*format == 'X')
		count = ft_putnbr_base(va_arg(ap, unsigned int), HEXAUP, count);
	else if (*format == '%')
		count = ft_putchar_printf('%', count);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count = ft_list_conditions(format, ap, count);
		}
		else
			count = ft_putchar_printf(*format, count);
		format++;
	}
	va_end(ap);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	nb;
// 	int	count;
// 	void	*ptr;

// 	nb = -42;
// 	ptr = -1;
// 	count = ft_printf("%p\n", ptr);
// 	ft_printf("%d\n", count);
// 	count = printf("%p\n", ptr);
// 	printf("%d\n", count);
// 	return (0);
// }
