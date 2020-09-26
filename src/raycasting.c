#include "../inc/cub3d.h"

void	ft_get_texture(t_recup *recup)
{
	recup->texture[0].mlx_ptr = mlx_init();
	recup->texture[1].mlx_ptr = mlx_init();
	recup->texture[2].mlx_ptr = mlx_init();
	recup->texture[3].mlx_ptr = mlx_init();
	recup->texture[4].mlx_ptr = mlx_init();
	if (!(recup->texture[0].img = mlx_xpm_file_to_image(recup->texture[0].mlx_ptr, \
			recup->NO, &(recup->texture[0].width), &(recup->texture[0].height))))
			printf("erreur texture NO\n");
	if (!(recup->texture[1].img = mlx_xpm_file_to_image(recup->texture[1].mlx_ptr, \
			recup->SO, &(recup->texture[1].width), &(recup->texture[1].height))))
			printf("erreur texture SO\n");
	if (!(recup->texture[2].img = mlx_xpm_file_to_image(recup->texture[2].mlx_ptr, \
			recup->WE, &(recup->texture[2].width), &(recup->texture[2].height))))
			printf("erreur texture WE\n");
	if (!(recup->texture[3].img = mlx_xpm_file_to_image(recup->texture[3].mlx_ptr, \
			recup->EA, &(recup->texture[3].width), &(recup->texture[3].height))))
			printf("erreur texture EA\n");
	if (!(recup->texture[4].img = mlx_xpm_file_to_image(recup->texture[4].mlx_ptr, \
			recup->S, &(recup->texture[4].width), &(recup->texture[4].height))))
			printf("erreur texture S\n");
	recup->texture[0].addr = mlx_get_data_addr(recup->texture[0].img, &recup->texture[0].bits_per_pixel, \
	 		&recup->texture[0].line_length, &recup->texture[0].endian);
	recup->texture[1].addr = mlx_get_data_addr(recup->texture[1].img, &recup->texture[1].bits_per_pixel, \
	 		&recup->texture[1].line_length, &recup->texture[1].endian);
	recup->texture[2].addr = mlx_get_data_addr(recup->texture[2].img, &recup->texture[2].bits_per_pixel, \
	 		&recup->texture[2].line_length, &recup->texture[2].endian);
	recup->texture[3].addr = mlx_get_data_addr(recup->texture[3].img, &recup->texture[3].bits_per_pixel, \
	 		&recup->texture[3].line_length, &recup->texture[3].endian);
	recup->texture[4].addr = mlx_get_data_addr(recup->texture[4].img, &recup->texture[4].bits_per_pixel, \
	 		&recup->texture[4].line_length, &recup->texture[4].endian);
}

int		ft_raycasting(t_recup *recup)
{
	ft_minimap(recup);
	recup->ray.x = 0;
	while (recup->ray.x < recup->Rx) //seulement x car on imprime par bande
	{
		ft_initialisation3(recup);
		ft_stepsideDist(recup);
		ft_incrementray(recup);
		ft_drawStartEnd(recup);
		ft_color_column(recup);
		recup->ray.x++;
	}
	ft_sprite(recup);
	ft_hitpoints(recup);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win, recup->data.img, 0, 0);
	return (0);
}

int		ft_mlx(t_recup *recup)
{
	//int i = 0;
	ft_initialisation2(recup);
	ft_get_texture(recup);
	recup->data.mlx_ptr = mlx_init();
	recup->data.mlx_win = mlx_new_window(recup->data.mlx_ptr, recup->Rx, recup->Ry, "Hello world!");
	recup->data.img = mlx_new_image(recup->data.mlx_ptr, recup->Rx, recup->Ry);
	recup->data.addr = mlx_get_data_addr(recup->data.img, &recup->data.bits_per_pixel, \
			&recup->data.line_length, &recup->data.endian);

	mlx_hook(recup->data.mlx_win, 2, 1L<<0, ft_key_press, recup);
	mlx_loop_hook(recup->data.mlx_ptr, ft_raycasting, recup);
	printf("recup->s.nbspr : %d\n", recup->s.nbspr);
	/*while (i < recup->s.nbspr)
	{
		printf("recup->s.dist[%d] = %f\n", i, recup->s.dist[i]);
		printf("recup->s.order[%d] = %d\n", i, recup->s.order[i]);
		i++;
	}*/
	mlx_hook(recup->data.mlx_win, 3, 1L<<1, ft_key_release, recup);
	mlx_loop(recup->data.mlx_ptr);
	return (0);
}
