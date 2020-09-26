#include "../inc/cub3d.h"

void	ft_stepsideDist(t_recup *recup) //calcul de stepX, stepY, sideDistX et sideDistY
{
		if (recup->ray.rayDirX < 0)
		{
			recup->ray.stepX = -1;
			recup->ray.sideDistX = (recup->ray.posX - recup->ray.mapX) * recup->ray.deltaDistX;
		}
		else
		{
			recup->ray.stepX = 1;
			recup->ray.sideDistX = (recup->ray.mapX + 1.0 - recup->ray.posX) * recup->ray.deltaDistX;
		}
		if (recup->ray.rayDirY < 0)
		{
			recup->ray.stepY = -1;
			recup->ray.sideDistY = (recup->ray.posY - recup->ray.mapY) * recup->ray.deltaDistY;
		}
		else
		{
			recup->ray.stepY = 1;
			recup->ray.sideDistY = (recup->ray.mapY + 1.0 - recup->ray.posY) * recup->ray.deltaDistY;
		}
}

void	ft_incrementray(t_recup *recup) //tant qu'on a pas touche un mur on passe au carre suivant soit dans la direction x soit direction y
{
	while (recup->ray.hit == 0)
	{
		if (recup->ray.sideDistX < recup->ray.sideDistY) // intersection avec un cote x (vertical)
		{
			recup->ray.sideDistX += recup->ray.deltaDistX;
			recup->ray.mapX += recup->ray.stepX;
			recup->ray.side = 0;
		}
		else //intersection avec un cote y (horizontal)
		{
			recup->ray.sideDistY += recup->ray.deltaDistY;
			recup->ray.mapY += recup->ray.stepY;
			recup->ray.side = 1;
		}
		if (recup->map[recup->ray.mapX][recup->ray.mapY] == '1')
			recup->ray.hit = 1;
		}
}

void	ft_drawStartEnd(t_recup *recup)
{
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (recup->ray.side == 0)
			recup->ray.perpWallDist = ((double)recup->ray.mapX - recup->ray.posX + (1 - (double)recup->ray.stepX) / 2) / recup->ray.rayDirX;
		else
			recup->ray.perpWallDist = ((double)recup->ray.mapY - recup->ray.posY + (1 - (double)recup->ray.stepY) / 2) / recup->ray.rayDirY;
	// calcul de la hauteur de la ligne a dessiner	
		recup->ray.lineHeight = (int)(recup->Ry / recup->ray.perpWallDist);
		recup->ray.drawStart = - recup->ray.lineHeight / 2 + recup->Ry / 2;
		if (recup->ray.drawStart < 0)
			recup->ray.drawStart = 0;
		recup->ray.drawEnd = recup->ray.lineHeight / 2 + recup->Ry / 2;
		if (recup->ray.drawEnd >= recup->Ry)
			recup->ray.drawEnd = recup->Ry - 1;
		if (recup->map[recup->ray.mapX][recup->ray.mapY] == '1')
		{
			recup->ray.color = 22620000;
			if (recup->ray.side == 1)
				recup->ray.color = 22520000;
		}
}
