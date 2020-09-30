#include "../inc/cub3d.h"

void    ft_forward_back(t_recup *recup)
{
    if (recup->data.forward == 1)
	{
		if (recup->map[(int)(recup->ray.posX + recup->ray.dirX)][(int)recup->ray.posY] != '1')
			recup->ray.posX += recup->ray.dirX * recup->ray.movespeed;
		if (recup->map[(int)(recup->ray.posX)][(int)(recup->ray.posY + recup->ray.dirY)] != '1') 
			recup->ray.posY += recup->ray.dirY * recup->ray.movespeed;
	}
    if (recup->data.back == 1)
	{
		if (recup->map[(int)(recup->ray.posX - recup->ray.dirX)][(int)(recup->ray.posY)] != '1') 
			recup->ray.posX -= recup->ray.dirX * recup->ray.movespeed;
		if (recup->map[(int)(recup->ray.posX)][(int)(recup->ray.posY - recup->ray.dirY)] != '1') 
			recup->ray.posY -= recup->ray.dirY * recup->ray.movespeed;
	}
}

void	ft_left_right(t_recup *recup)
{
	if (recup->data.right == 1)
	{
		if (recup->map[(int)(recup->ray.posX + recup->ray.dirY *
					recup->ray.movespeed)][(int)recup->ray.posY] != '1')
			recup->ray.posX += recup->ray.dirY * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posX][(int)(recup->ray.posY - recup->ray.dirX *
					recup->ray.movespeed)] != '1')
			recup->ray.posY -=  recup->ray.dirX * recup->ray.movespeed;
	}
	if (recup->data.left == 1)
	{
		if (recup->map[(int)(recup->ray.posX - recup->ray.dirY *
					recup->ray.movespeed)][(int)recup->ray.posY] != '1')
			recup->ray.posX -= recup->ray.dirY * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posX][(int)(recup->ray.posY + recup->ray.dirX *
					recup->ray.movespeed)] != '1')
			recup->ray.posY +=  recup->ray.dirX * recup->ray.movespeed;
	}
}

void    ft_rotate_right_left(t_recup *recup)
{
    if (recup->data.rotate_right == 1)
	{
		double oldDirX = recup->ray.dirX;
		recup->ray.dirX = recup->ray.dirX * cos(-recup->ray.rotspeed / 2) - recup->ray.dirY * sin(-recup->ray.rotspeed / 2);
		recup->ray.dirY = oldDirX * sin(-recup->ray.rotspeed / 2) + recup->ray.dirY * cos(-recup->ray.rotspeed / 2);
		double oldPlanX = recup->ray.planX;
		recup->ray.planX = recup->ray.planX * cos(-recup->ray.rotspeed / 2) - recup->ray.planY * sin(-recup->ray.rotspeed / 2);
		recup->ray.planY = oldPlanX * sin(-recup->ray.rotspeed / 2) + recup->ray.planY * cos(-recup->ray.rotspeed / 2);
	}
    if (recup->data.rotate_left == 1)
	{
		double oldDirX = recup->ray.dirX;
		recup->ray.dirX = recup->ray.dirX * cos(recup->ray.rotspeed / 2) - recup->ray.dirY * sin(recup->ray.rotspeed / 2);
		recup->ray.dirY = oldDirX * sin(recup->ray.rotspeed / 2) + recup->ray.dirY * cos(recup->ray.rotspeed / 2);
		double oldPlaneX = recup->ray.planX;
		recup->ray.planX = recup->ray.planX * cos(recup->ray.rotspeed / 2) - recup->ray.planY * sin(recup->ray.rotspeed / 2);
		recup->ray.planY = oldPlaneX * sin(recup->ray.rotspeed / 2) + recup->ray.planY * cos(recup->ray.rotspeed / 2);
	}
}
