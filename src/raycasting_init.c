#include "../inc/cub3d.h"

void	ft_initialisation2(t_recup *recup)
{
	if (!(recup->s.ZBuffer = (double *)malloc(sizeof(double) * recup->Rx)))
		exit(0);
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
	recup->ray.cameraX = 2 * recup->ray.x / (double)recup->Rx - 1;
	//calcul de la position du rayon sur le plan de la camera
	recup->ray.rayDirX = recup->ray.dirX + recup->ray.planX * \
						recup->ray.cameraX; //calcul de direction x du rayon
	recup->ray.rayDirY = recup->ray.dirY + recup->ray.planY * \
						recup->ray.cameraX; //calcul de direction y du rayon
	recup->ray.mapX = (int)recup->ray.posX;
	recup->ray.mapY = (int)recup->ray.posY;
	recup->ray.movespeed = 0.1;
	recup->ray.rotspeed = 0.033 * 1.8;
	recup->ray.deltaDistX = (recup->ray.rayDirY == 0) ? 0 : \
			((recup->ray.rayDirX == 0) ? 1 : sqrt(1 + (recup->ray.rayDirY * \
			recup->ray.rayDirY) / (recup->ray.rayDirX * recup->ray.rayDirX)));
	recup->ray.deltaDistY = (recup->ray.rayDirX == 0) ? 0 : \
			((recup->ray.rayDirY == 0) ? 1 : sqrt(1 + (recup->ray.rayDirX * \
			recup->ray.rayDirX) / (recup->ray.rayDirY * recup->ray.rayDirY)));
}

void	ft_init_texture(t_recup *recup)
{
	if (recup->ray.side == 0 && recup->ray.rayDirX < 0) //NO
		recup->t.texdir = 0;
	if (recup->ray.side == 0 && recup->ray.rayDirX >= 0) // S
		recup->t.texdir = 1;
	if (recup->ray.side == 1 && recup->ray.rayDirY < 0) // WE
		recup->t.texdir = 2;
	if (recup->ray.side == 1 && recup->ray.rayDirY >= 0) // EA
		recup->t.texdir = 3;
	if (recup->ray.side == 0)
		recup->t.wallX = recup->ray.posY + recup->ray.perpWallDist \
						* recup->ray.rayDirY;
	else
		recup->t.wallX = recup->ray.posX + recup->ray.perpWallDist \
						* recup->ray.rayDirX;
	recup->t.wallX -= floor((recup->t.wallX)); // wallX = 15.3 devient wallX = 0.3
}

//initialise recup->sxy[].x, recup->sxy[].y pour chaque sprite + nbspr + mallocs
void	ft_init_sprite(t_recup *recup)
{
	int i;
	int j;

	i = 0;
	j = 0;
	recup->s.nbspr = 0;
	while (i < recup->nblines)
	{
		j = 0;
		while (j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
				recup->s.nbspr += 1;
			j++;
		}
		i++;
	}
	if (!(recup->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * recup->s.nbspr)))
		ft_error(recup, "Malloc sxy*");
	if (!(recup->s.order = (int *)malloc(sizeof(int) * recup->s.nbspr)))
		ft_error(recup, "Malloc s.order*");
	if (!(recup->s.dist = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error(recup, "Malloc s.dist*");
	ft_init_sprite2(recup, 0, 0, 0);
}

void	ft_init_sprite2(t_recup *recup, int i, int j, int v)
{
	while (i < recup->nblines)
	{
		j = 0;
		while (j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
			{
				recup->sxy[v].x = (double)i + 0.5;
				recup->sxy[v].y = (double)j + 0.5;
				v++;
			}
			j++;
		}
		i++;
	}
}
