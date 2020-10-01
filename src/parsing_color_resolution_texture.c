/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_resolution_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/01 16:38:45 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_atoi2(const char *str, t_recup *recup)
{
	int		sum;

	sum = 0;
	if (str[1] != ' ')
		ft_error(recup, "Identifiant R incorrect\n");
	while (str[recup->i] == ' ' || str[recup->i] == '\t'
			|| str[recup->i] == ',' || str[recup->i] == '\n'
			|| str[recup->i] == '\r' || str[recup->i] == '\v'
			|| str[recup->i] == '\f')
		recup->i++;
	if (str[recup->i] == '-' || str[recup->i] == '+')
		ft_error(recup, "Signe dans la resolution\n");
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
	{
		sum = (sum * 10) + (str[recup->i] - 48);
		recup->i++;
	}
	return (sum);
}

int		ft_atoi3(const char *str, t_recup *recup)
{
	int		sum;
	int		verify;

	verify = 0;
	sum = 0;
	if (str[1] != ' ')
		ft_error(recup, "Identifiant F ou C incorrect\n");
	while (str[recup->i] == ' ' || str[recup->i] == '\t' || str[recup->i]
			== ',' || str[recup->i] == '\n' || str[recup->i] == '\r'
			|| str[recup->i] == '\v' || str[recup->i] == '\f')
	{
		recup->i++;
		verify = 0;
		if (str[recup->i] >= '0' && str[recup->i] <= '9')
			recup->indicateur2++;
		while (str[recup->i] >= '0' && str[recup->i] <= '9')
		{
			verify = (verify * 10) + str[recup->i] - 48;
			sum = (sum * 10) + (str[recup->i] - 48);
			recup->i++;
		}
		if (verify > 255)
			ft_error(recup, "Chiffre superieur a 255 dans F ou C\n");
	}
	return (sum);
}

char	*ft_path_texture(char *str, t_recup *recup, int j)
{
	int		i;
	char	*copie;

	i = 0;
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
			|| ft_strlen2(str) <= 2)
		ft_error(recup, "Path texture invalide\n");
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			ft_error(recup, "Identifiant ou path texture invalide");
		j++;
	}
	if (!(copie = (malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		return (NULL);
	while (str[j] != '\0')
	{
		copie[i] = str[j];
		i++;
		j++;
	}
	copie[i] = '\0';
	return (copie);
}

void	ft_texture(char *str, t_recup *recup)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		recup->NO = ft_path_texture(str, recup, 2);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		recup->SO = ft_path_texture(str, recup, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		recup->WE = ft_path_texture(str, recup, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		recup->EA = ft_path_texture(str, recup, 2);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		recup->S = ft_path_texture(str, recup, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
			&& str[0] > 65 && str[0] < 122)
		ft_error(recup \
				, "Premier caractere d'un element n'est pas un identifiant\n");
	j++;
}

void	ft_color_resolution(char *str, t_recup *recup)
{
	int			i;

	i = 0;
	recup->i = 1;
	if (recup->sizeline > 0 && (recup->NO == NULL || recup->SO == NULL ||
				recup->WE == NULL || recup->EA == NULL || recup->S == NULL))
		ft_error(recup, "Map avant elements ou elements manquants\n");
	if (str[i] == 'R')
	{
		recup->Rx = ft_atoi2(str, recup);
		recup->Ry = ft_atoi2(str, recup);
		if (ft_atoi2(str, recup) > 0 || recup->Rx == 0 || recup->Ry == 0)
			ft_error(recup, "Mauvais nombre de chiffres dans R\n");
	}
	else if (str[i] == 'F')
		recup->F = ft_atoi3(str, recup);
	else if (str[i] == 'C')
		recup->C = ft_atoi3(str, recup);
}
