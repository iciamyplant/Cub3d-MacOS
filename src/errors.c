/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/07 18:51:53 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_verify_errors(t_recup *recup)
{
	if (ft_murs(recup) == 1)
		ft_error(recup, "Map non entouree de 1\n");
	if (recup->depart == 'x')
		ft_error(recup, "Pas de joueur\n");
	if (recup->indicateur2 != 6)
		ft_error(recup, "Mauvaises donnees F ou C\n");
}

void	ft_error(t_recup *recup, char *str)
{
	int i;

	i = -1;
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));

/////////////////free textures
	if (recup->NO)
		free(recup->NO);
	if (recup->SO)
		free(recup->SO);
	if (recup->WE)
		free(recup->WE);
	if (recup->EA)
		free(recup->EA);
	if (recup->S)
		free(recup->S);

/////////////////free la map
	if (recup->map)
	{
		while (++i < recup->nblines)
			free(recup->map[i]);
	}
	if (recup->map)
		free(recup->map);

/////////////////free sorder, sdist, sxy
	if (recup->s.order)
		free(recup->s.order);
	if (recup->s.dist)
		free(recup->s.dist);
//	if (recup->sxy)
//		free(recup->sxy);

//////////////////free zbuffer
//	if (recup->s.Zbuffer)
//		free(recup->s.Zbuffer);


/*	while (i != 0)
	{
		system("leaks Cub3D");
	}*/
	ft_exit(recup);
}

int		ft_exit(t_recup *recup)
{
	if (recup->data.img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->data.img);
	if (recup->texture[0].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[0].img);
	if (recup->texture[1].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[1].img);
	if (recup->texture[2].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[2].img);
	if (recup->texture[3].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[3].img);
	if (recup->texture[4].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[4].img);
	if (recup->data.mlx_win)
		mlx_destroy_window(recup->data.mlx_ptr, recup->data.mlx_win);
	exit(0);
}

void			ft_header(t_recup *recup, int fd)
{
	int tmp;

	write(fd, "BM", 2); //BM indique qu'il s'agit d'un Bitmap.
	tmp = 14 + 40 + 4 * recup->Rx * recup->Ry; //taille totale du fichier
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2); //champ réservé
	write(fd, &tmp, 2);
	tmp = 54; //offset de l'image
	write(fd, &tmp, 4);
	tmp = 40; //taille image en octets
	write(fd, &tmp, 4);
	write(fd, &recup->Rx, 4); //taille image horizontalement
	write(fd, &recup->Ry, 4); //taille image verticalement
	tmp = 1; //nombre de plans (toujours 1)
	write(fd, &tmp, 2);
	write(fd, &recup->data.bits_per_pixel, 2); //nombre de bits utilisés pour coder la couleur
	tmp = 0; //methode de compression 0 si image non compressee
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_recup *recup)
{
	int fd;
	int	x;
	int	y;

	y = recup->Ry;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(recup, "Impossible de creer .bmp\n");
	ft_header(recup, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < recup->Rx)
		{
			write(fd, &recup->data.addr[y * recup->data.line_length / 4 + x], 4);
			x++;
		}
		y--;
	}
	system("chmod 777 image.bmp"); //pour pouvoir voir limage dans le finder
	exit (0);
}
