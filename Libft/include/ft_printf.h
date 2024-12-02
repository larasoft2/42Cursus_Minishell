/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:31:16 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 13:30:08 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define BASE10 "0123456789"
# define HEXALOW "0123456789abcdef"
# define HEXAUP "0123456789ABCDEF"

int	ft_putchar_printf(char c, int count_final);
int	ft_putstr_printf(char *str, int count_final);
int	ft_strlen_printf(char *str);
int	ft_putnbr_base(long nbr, char *base, int count_final);
int	ft_putnbr_base_long(unsigned long long nbr, char *base, int count_final);
int	count_number_length(long nbr, char *base, int count_final);
int	count_number_length_p(unsigned long long nbr, char *base, int count_final);
int	ft_pointer(unsigned long long ptr, int count);
int	ft_list_conditions(const char *format, va_list ap, int count);
int	ft_printf(const char *format, ...);

#endif
