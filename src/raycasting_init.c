#include "../inc/cub3d.h"

void	ft_initialisation2(t_recup *recup)
{
	recup->data.forward = 0;
	recup->data.back = 0;
	recup->data.left = 0;
	recup->data.right = 0;
	recup->data.rotate_right = 0;
	recup->data.rotate_left = 0;
	recup->ray.posX = (double)recup->dx;
	recup->ray.posY = (double)recup->dy;
	ft_orientationdir(recup); //initialise dirX et dirY selon N S E W initial
	ft_orientationplan(recup); //initialise planX et planY selon N S E W initial
}

void	ft_initialisation3(t_recup *recup)
{
	recup->ray.hit = 0;
	recup->ray.cameraX = 0;
	recup->ray.perpWallDist = 0;
	recup->ray.color = 0;
    recup->ray.cameraX = 2 * recup->ray.x / (double)recup->Rx - 1; //calcul de la position du rayon sur le plan de la camera
	recup->ray.rayDirX = recup->ray.dirX + recup->ray.planX * recup->ray.cameraX; //calcul de direction x du rayon
	recup->ray.rayDirY = recup->ray.dirY + recup->ray.planY * recup->ray.cameraX; //calcul de direction y du rayon
	recup->ray.mapX = (int)recup->ray.posX;
	recup->ray.mapY = (int)recup->ray.posY;
	recup->ray.movespeed = 0.1;
	recup->ray.rotspeed = 0.033 * 1.8;
	recup->ray.deltaDistX = (recup->ray.rayDirY == 0) ? 0 : ((recup->ray.rayDirX == 0) ? 1 : sqrt(1 + (recup->ray.rayDirY * recup->ray.rayDirY) / (recup->ray.rayDirX * recup->ray.rayDirX)));
	recup->ray.deltaDistY = (recup->ray.rayDirX == 0) ? 0 : ((recup->ray.rayDirY == 0) ? 1 : sqrt(1 + (recup->ray.rayDirX * recup->ray.rayDirX) / (recup->ray.rayDirY * recup->ray.rayDirY)));
}

void	ft_orientationdir(t_recup *recup)
{
	if (recup->depart == 'N')
	{
		recup->ray.dirX = -1;
		recup->ray.dirY = 0;
	}
	if (recup->depart == 'S')
	{
		recup->ray.dirX = 1;
		recup->ray.dirY = 0;
	}
	if (recup->depart == 'E')
	{
		recup->ray.dirX = 0;
		recup->ray.dirY = 1;
	}
	if (recup->depart == 'W')
	{
		recup->ray.dirX = 0;
		recup->ray.dirY = -1;
	}
}

void	ft_orientationplan(t_recup *recup)
{
	if (recup->depart == 'N')
	{
		recup->ray.planX = 0;
		recup->ray.planY = 0.66;
	}
	if (recup->depart == 'S')
	{
		recup->ray.planX = 0;
		recup->ray.planY = -0.66;
	}
	if (recup->depart == 'E')
	{
		recup->ray.dirX = 0.66;
		recup->ray.dirY = 0;
	}
	if (recup->depart == 'W')
	{
		recup->ray.dirX = -0.66;
		recup->ray.dirY = 0;
	}
}

void	ft_init_texture(t_recup *recup)
{
	if (recup->ray.side == 0 && recup->ray.rayDirX < 0) // NO
		recup->t.texdir = 0;
	if (recup->ray.side == 0 && recup->ray.rayDirX >= 0) // S
		recup->t.texdir = 1; 
	if (recup->ray.side == 1 && recup->ray.rayDirY < 0) // WE
		recup->t.texdir = 2;
	if (recup->ray.side == 1 && recup->ray.rayDirY >= 0) // EA
		recup->t.texdir = 3;
	
	if (recup->ray.side == 0)
		recup->t.wallX = recup->ray.posY + recup->ray.perpWallDist * recup->ray.rayDirY; 
	else
		recup->t.wallX = recup->ray.posX + recup->ray.perpWallDist * recup->ray.rayDirX;
	recup->t.wallX -= floor((recup->t.wallX)); // wallX = 15.3 devient wallX = 0.3
}
