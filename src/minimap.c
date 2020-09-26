#include "../inc/cub3d.h"

void	my_color_cube(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	j = 0;
	while (j < data->minimapechelle)
	{
		i = 0;
		while (i < data->minimapechelle)
		{
			my_mlx_pixel_put(data, y + i, x + j, color);
			i++;
		}
		j++;
	}
}

void	my_color_perso(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	j = 0;
	while (j < (data->minimapechelle / 3))
	{
		i = 0;
		while (i < (data->minimapechelle / 3))
		{
			my_mlx_pixel_put(data, y + i, x + j, color);
			i++;
		}
		j++;
	}
}

int		ft_minimap(t_recup *recup)
{
	int x;
	int i;
	int j;
	int y;

	x = 40;
	y = 40;
	j = 0;
	recup->data.minimapechelle = ((int)recup->Rx * 0.012);
	while (j < recup->nblines)
	{
		i = 0;
		y = 40;
		while (i < recup->sizeline)
		{
			if (recup->map[j][i] == '1')
				my_color_cube(&recup->data, x, y, 22520000);
			if (recup->map[j][i] == '0')
				my_color_cube(&recup->data, x, y, 225248220);
			if (recup->map[j][i] == '2')
				my_color_cube(&recup->data, x, y, 802020);
			if (j == (int)recup->ray.posX && i == (int)recup->ray.posY)
				my_color_perso(&recup->data, x, y, 255000000);
			i++;
			y = y + recup->data.minimapechelle;
		}
		x = x + recup->data.minimapechelle;
		j++;
	}
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win, recup->data.img, 0, 0);
	return (0);
}
