#include "../inc/cub3d.h"

void	ft_dist_order(t_recup *recup)
{
	int		i = 0;
	int		j = 0;
	double	tmp;

	// Calculez la distance de chaque sprite au joueur
	while (i < recup->s.nbspr)
	{
		recup->s.order[i] = i;
		recup->s.dist[i] = ((recup->ray.posX - recup->sxy[i].x) *
				(recup->ray.posX - recup->sxy[i].x) + (recup->ray.posY -
					recup->sxy[i].y) * (recup->ray.posY - recup->sxy[i].y));
		i++;
	}
	// utilisez cette distance pour trier les sprites, du plus éloigné au plus proche de la caméra
	i = 0;
	while (i < recup->s.nbspr)
	{
		j = 0;
		while (j < recup->s.nbspr - 1)
		{
			if (recup->s.dist[j] < recup->s.dist[j + 1])
			{
				tmp = recup->s.dist[j];
				recup->s.dist[j] = recup->s.dist[j + 1];
				recup->s.dist[j + 1] = tmp;
				tmp = recup->s.order[j];
				recup->s.order[j] = recup->s.order[j + 1];
				recup->s.order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_calculs(t_recup *recup, int i)
{
	recup->s.spriteX = recup->sxy[recup->s.order[i]].x - recup->ray.posX;
	recup->s.spriteY = recup->sxy[recup->s.order[i]].y - recup->ray.posY;
	recup->s.invDet = 1.0 / (recup->ray.planX * recup->ray.dirY - recup->ray.dirX * recup->ray.planY);
	recup->s.transformX = recup->s.invDet * (recup->ray.dirY * recup->s.spriteX - recup->ray.dirX * recup->s.spriteY);
  	recup->s.transformY = recup->s.invDet * (-recup->ray.planY * recup->s.spriteX + recup->ray.planX * recup->s.spriteY);
	recup->s.spriteScreenX = (int)((recup->Rx / 2) * (1 + recup->s.transformX / recup->s.transformY));
	recup->s.spriteHeight = abs((int)(recup->Ry / (recup->s.transformY)));
	recup->s.drawStartY = -recup->s.spriteHeight / 2 + recup->Ry / 2;
	if (recup->s.drawStartY < 0) 
		recup->s.drawStartY = 0;
   	recup->s.drawEndY = recup->s.spriteHeight / 2 + recup->Ry / 2;
   	if (recup->s.drawEndY >= recup->Ry) 
		recup->s.drawEndY = recup->Ry - 1;
	recup->s.spriteWidth = abs((int)(recup->Ry / (recup->s.transformY)));
 	recup->s.drawStartX = -recup->s.spriteWidth / 2 + recup->s.spriteScreenX;
  	if (recup->s.drawStartX < 0) 
		recup->s.drawStartX = 0;
    recup->s.drawEndX = recup->s.spriteWidth / 2 + recup->s.spriteScreenX;
    if (recup->s.drawEndX >= recup->Rx) 
		recup->s.drawEndX = recup->Rx - 1;
}

void	ft_draw_spr(t_recup *recup, int y, int texX, int stripe)
{
	int 	d;
	int		texY;
	char	*dst;
	char	*dst2;

	while (y < recup->s.drawEndY)
	{
		d = (y) * 256 - recup->Ry * 128 + recup->s.spriteHeight * 128;
		texY = ((d * recup->texture[4].height) / recup->s.spriteHeight) / 256;
		if (recup->texture[4].addr + (texX * (recup->texture[4].bits_per_pixel / 8) + texY * recup->texture[4].line_length))
		{
			dst = (char *)recup->texture[4].addr + (texX * (recup->texture[4].bits_per_pixel / 8) + texY * recup->texture[4].line_length);
			dst2 = (char *)recup->data.addr + (stripe * (recup->data.bits_per_pixel / 8) + y * recup->data.line_length);
			if (*(unsigned int*)dst != 000)
				*(unsigned int*)dst2 = *(unsigned int*)dst;
		}
		y++;
	}
}

void	ft_sprite(t_recup *recup)
{
	int i = 0;
	int y;
	int stripe;
	int texX;

	ft_dist_order(recup);
	while (i < recup->s.nbspr)
	{
		ft_calculs(recup, i);
		stripe = recup->s.drawStartX;
		while (stripe < recup->s.drawEndX)
		{
			texX = (int)(256 * (stripe - (-recup->s.spriteWidth / 2 + recup->s.spriteScreenX)) * recup->texture[4].width / recup->s.spriteWidth) / 256;
			if (recup->s.transformY > 0 && stripe > 0 && stripe < recup->Rx && recup->s.transformY < recup->s.ZBuffer[stripe])
			{
				y = recup->s.drawStartY;
				ft_draw_spr(recup, y, texX, stripe);
			}
			stripe++;
		}
		i++;
	}
}
