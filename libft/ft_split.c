/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:46:30 by vserra            #+#    #+#             */
/*   Updated: 2019/11/17 09:51:17 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char *str, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c && i == 0)
		{
			word++;
			i++;
		}
		if (str[i] != c && str[i - 1] == c)
			word++;
		i++;
	}
	return (word);
}

static int	ft_len_word(char *str, char c)
{
	int		len;

	len = 0;
	while (str[len])
	{
		if (str[len] != c)
			len++;
		else
			break ;
	}
	return (len);
}

static char	**ft_free(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*ft_dup(char *src, char c)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = ft_len_word(src, c);
	if ((dst = malloc(sizeof(*src) * (len + 1))) == NULL)
		return (NULL);
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		**ft_split(char const *s, char c)
{
	char	*str;
	char	**tab;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)s;
	words = ft_count_word(str, c);
	if ((tab = ft_calloc(words + 1, sizeof(*tab))) == NULL)
		return (NULL);
	tab[words] = NULL;
	i = 0;
	while (*str)
		if (*str != c)
		{
			if ((tab[i] = ft_dup(str, c)) == NULL)
				return (ft_free(tab));
			i++;
			str += ft_len_word(str, c);
		}
		else
			str++;
	return (tab);
}
