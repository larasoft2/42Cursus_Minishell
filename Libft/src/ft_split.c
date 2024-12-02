/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racoutte <racoutte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:23:33 by racoutte          #+#    #+#             */
/*   Updated: 2024/08/13 14:42:32 by racoutte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_countwords(const char *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		while (s[i])
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
				nb_words++;
			i++;
		}
	}
	return (nb_words);
}

static char	*ft_write_word(const char *s, char *str, int i, int size_word)
{
	int	k;

	k = 0;
	while (size_word > 0)
	{
		str[k] = s[i - size_word];
		k++;
		size_word--;
	}
	str[k] = '\0';
	return (str);
}

static char	**ft_filling_array(const char *s, char c, int nb_words, char **tab)
{
	int	i;
	int	j;
	int	size_word;

	i = 0;
	j = 0;
	while (j < nb_words)
	{
		size_word = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			size_word++;
			i++;
		}
		tab[j] = (char *) malloc(sizeof(char) * (size_word + 1));
		if (!tab[j])
		{
			ft_free(tab, j);
			return (NULL);
		}
		ft_write_word(s, tab[j++], i, size_word);
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_countwords(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	tab = ft_filling_array(s, c, nb_words, tab);
	if (!tab)
		return (NULL);
	tab[nb_words] = NULL;
	return (tab);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	int	nb;
// 	int	i;
// 	char	**tab;

// 	i = 0;
// 	nb = ft_countwords(av[1], 32);
// 	printf("%d\n", nb);
// 	tab = ft_split(av[1], 32);
// 	while (i < nb)
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }
