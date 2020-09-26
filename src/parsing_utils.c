/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:19:22 by ebourdit          #+#    #+#             */
/*   Updated: 2020/09/17 16:02:15 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_strlen2(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int		ft_atoi2(const char *str, t_recup *recup)
{
	int signe;
	int sum;

	sum = 0;
	signe = 1;
	while (str[recup->i] == ' ' || str[recup->i] == '\t' || str[recup->i] == ',' || str[recup->i] == '\n'
			|| str[recup->i] == '\r' || str[recup->i] == '\v' || str[recup->i] == '\f')
		recup->i++;
	if (str[recup->i] == '-' || str[recup->i] == '+')
	{
		if (str[recup->i] == '-')
			signe = -1;
		recup->i++;
	}
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
	{
		sum = (sum * 10) + (str[recup->i] - 48);
		recup->i++;
	}
	return (sum * signe);
}

int		ft_atoi3(const char *str, t_recup *recup)
{
	int sum;
	sum = 0;
	while (str[recup->i] == ' ' || str[recup->i] == '\t' || str[recup->i] == ',' || str[recup->i] == '\n'
			|| str[recup->i] == '\r' || str[recup->i] == '\v' || str[recup->i] == '\f')
	{
		recup->i++;
		while (str[recup->i] >= '0' && str[recup->i] <= '9')
		{
			sum = (sum * 10) + (str[recup->i] - 48);
			recup->i++;
		}
	}
	return (sum);
}

int		ft_charinstr(char *str, char c)
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int  ft_depart(char c, t_recup *recup, int i, int j)
{
  if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
  {
    recup->depart = c;
    recup->dx = i;
    recup->dy = j;
    return (1);
  }
  return (0);
}

//verifie que tous les caracteres de str sont des '1'
int   ft_murs_util(char *str)
{
  int i;
  i = 0;
  while (str[i] != '\0')
  {
    if (str[i] != '1')
      return (1);
    i++;
  }
  return (0);
}
