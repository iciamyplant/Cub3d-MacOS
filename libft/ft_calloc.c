/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:13:56 by vserra            #+#    #+#             */
/*   Updated: 2019/11/11 23:04:41 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** In tribute to our friend Doris.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void *nemo;

	if (!(nemo = malloc(count * size)))
		return (NULL);
	ft_bzero(nemo, count * size);
	return (nemo);
}
