/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:29:09 by lusavign          #+#    #+#             */
/*   Updated: 2025/02/10 12:50:23 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si export test > creer variable avec valeur NULL (ne s'affichera pas dans env)
//si export test= > creer variable avec valeur \0

//on ne traite pas l'ajout de variables dans env SANS export, ex: VAR="Hello"
//on traite uniquement l'ajout de variables avec export, ex: export VAR="Hello"
//donc toutes les variables sont exportables, meme les chaines vides, donc env affiche tout

//difference entre export et env:
//export = affiche toutes les variables exportables (qui peuvent etre transferees aux process enfants)
//env = affiche toutes les variables (exportables ou non !)

void	ft_env(t_exec *ex, t_env *env)
{
	if (ex->arg[1] != NULL)
	{
		print_error_exec_message(NO_SUCH_FILE_OR_DIRECTORY, ex->arg[1]);
		return ;
	}
	print_env(env);
}
