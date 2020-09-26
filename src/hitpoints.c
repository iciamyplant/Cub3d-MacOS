#include "../inc/cub3d.h"

void	ft_hitpoints(t_recup *recup)
{
	int x;
	int y;
	int i;
	int j;
	x = 20;
	i = 0;
	j = 0;

	y = ((int)recup->Rx * 0.87);
	while (i < 9)
	{
		my_color_cube(&recup->data, x, y, 255000000);
		i++;
		y = y + 10;
	//	x = x + ((int)recup->Rx * 0.9);
	}
}
