/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:28 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/04 17:27:50 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export with no options;
// sets environment variables
//
// export can set a null variable that won't show in env
// but will show when typing export
// export alone shows all variables

// export	a = $b
// export b = $a must not loop
//
// export sans $


// void    ft_export(t_exec *exec, t_env *env)
// {
// }
