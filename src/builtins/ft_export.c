/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusavign <lusavign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:55:28 by lusavign          #+#    #+#             */
/*   Updated: 2025/01/23 15:45:08 by lusavign         ###   ########.fr       */
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

//si export sans rien > afficher l'env (par ordre ascii)
//si export test > creer variable avec valeur NULL (ne s'affichera pas dans env)
//si export test= > creer variable avec valeur \0


// void    ft_export(t_exec *exec, t_env *env)
// {
// }