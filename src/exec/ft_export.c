/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:28 by lusavign          #+#    #+#             */
/*   Updated: 2024/12/19 16:27:34 by lusavign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// export with no options;
// sets environment variables
//
// export can set a null variable that won't show in env
// but will show when typing export
// export alone shows all variables

// export	a = $b
// export b = $a must not loop

// void    ft_export(t_exec *exec, t_env *env)
// {
// }