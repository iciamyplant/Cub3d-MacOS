#include "../inc/cub3d.h"

int		ft_key_press(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 1;
	else if (keycode == BACK_S_S)
		recup->data.back = 1;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 1;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 1;
	else if (keycode == 53)
		ft_exit(recup);
	return (1);
}

int   ft_key_release(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 0;
	else if (keycode == BACK_S_S)
		recup->data.back = 0;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 0;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 0;
	return (1);
}

int		ft_color_column(t_recup *recup)
{
	int j = -1;
	int i = recup->ray.drawEnd;
	//write(1, "ICI1\n", 5);
	while (++j <= recup->ray.drawStart)
		recup->data.addr[j * recup->data.line_length / 4 + recup->ray.x] = recup->C;
	//write(1, "ICI2\n", 5);
	if (j <= recup->ray.drawEnd)
		ft_draw_texture(recup, recup->ray.x, j);
	//write(1, "ICI3\n", 5);
	j = i - 1;
	while (++j < recup->Ry)
		recup->data.addr[j * recup->data.line_length / 4 + recup->ray.x] = recup->F;
	//write(1, "ICI4\n", 5);
	return (0);
}

void	ft_draw_texture(t_recup *recup, int x, int y)
{
	y = recup->ray.drawStart;
	//char	*dst;
	//char	*dst2;

	ft_init_texture(recup);
	recup->t.step = 1.0 * recup->texture[0].height / recup->ray.lineHeight;
	recup->t.texX = (int)(recup->t.wallX * (double)recup->texture[recup->t.texdir].width);
	//write(1, "LOL1\n", 5);
	if (recup->ray.side == 0 && recup->ray.rayDirX > 0) 
		recup->t.texX = recup->texture[recup->t.texdir].width - recup->t.texX - 1;
    if (recup->ray.side == 1 && recup->ray.rayDirY < 0) 
		recup->t.texX = recup->texture[recup->t.texdir].width - recup->t.texX - 1;
	recup->t.texPos = (recup->ray.drawStart - recup->Ry / 2 + recup->ray.lineHeight / 2) * recup->t.step;
	//write(1, "LOL2\n", 5);
	while (y++ <= recup->ray.drawEnd)
	{
		recup->t.texY = (int)recup->t.texPos & (recup->texture[recup->t.texdir].height - 1);
		recup->t.texPos += recup->t.step;
		//dst = (char *)recup->texture[recup->t.texdir].addr + (recup->t.texY * recup->texture[recup->t.texdir].line_length + recup->t.texX * (recup->texture[recup->t.texdir].bits_per_pixel / 8));
		//dst2 = (char *)recup->data.addr + (y * recup->data.line_length + x * (recup->data.bits_per_pixel / 8));
		//*(unsigned int*)dst2 = *(unsigned int*)dst;
		recup->data.addr[y * recup->data.line_length / 4 + x] = recup->texture[recup->t.texdir].addr[recup->t.texY * recup->texture[recup->t.texdir].line_length / 4 + recup->t.texX];
	}
	//write(1, "LOL3\n", 5);
}
