/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:26:19 by vserra            #+#    #+#             */
/*   Updated: 2019/11/15 00:59:04 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lenght compte la longueur de la chain a trimmer (s2).
** 1 : On zappe les charset du debut (!=NULL signifie pas de charset).
** 2 : On incremente len jusqu'a '\0'.
** 3 : On decompte les charset a la fin de la string.
*/

static int	ft_lenght(char *str, char *sep)
{
	int		i;
	int		len;

	i = 0;
	while (str[i] && ft_strchr(sep, str[i]) != NULL)
		i++;
	if (str[i] == '\0')
		return (-1);
	len = 0;
	while (str[i] != '\0')
	{
		i++;
		len++;
	}
	i--;
	while (ft_strchr(sep, str[i]) != NULL)
	{
		i--;
		len--;
	}
	return (len);
}

/*
** 1 : On commence par malloc s2 de la longeur len renvoyee par ft_lenght.
** 2 : On zappe les charset du debut (!=NULL signifie pas de charset).
** 3 : On copie len caracteres de str (trimee) dans s2.
*/

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	char	*s2;
	char	*sep;
	int		len;

	str = (char *)s1;
	sep = (char *)set;
	if (!s1 || !set)
		return (NULL);
	if (ft_lenght(str, sep) == -1)
		return (ft_strdup(""));
	len = ft_lenght(str, sep);
	if (!(s2 = malloc(sizeof(*s2) * (len + 1))))
		return (NULL);
	while (*str && ft_strchr(sep, *str) != NULL)
		str++;
	i = 0;
	while (i < len)
	{
		s2[i++] = *str;
		str++;
	}
	s2[i] = '\0';
	return (s2);
}
