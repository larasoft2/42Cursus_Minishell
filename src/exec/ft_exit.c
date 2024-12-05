/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:14:07 by licohen           #+#    #+#             */
/*   Updated: 2024/12/04 17:20:39 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int is_len_one(void)
{
    ft_putendl_fd("exit", 1);
    return (0);
}

static int not_num(void)
{
    ft_putendl_fd("minishell: exit: numeric argument required", 2);
    return (2);
}

static int too_many_args(void)
{
    ft_putendl_fd("minishell: exit: too many arguments", 2);
    return (1);
}

static int is_num(char *str)
{
    int i; 

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (ft_isdigit(str[i]))
        i++;
    if (str[i])
        return (0);
    return (1);
}

int ft_exit(char **array)
{
    int len;
    int code;

    len = nbr_of_args(array);
    if (len == 1)
        return (is_len_one());
    else if (!is_num(array[1]))
        return (not_num());
    else if (len > 2)
        return (too_many_args());
    code = ft_atoi(array[1]) % 256;
    if (code < 0)
        code += 256;
    ft_putendl_fd("exit", 1);
    return (code);
}