#ifndef _CUB3D_H
# define _CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "libft.h"

# define ROTATE_LEFT		123
# define ROTATE_RIGHT		124
# define FORWARD_W_Z		13
# define BACK_S_S			1
# define RIGHT_D_D			2
# define LEFT_A_Q			0

// # ifndef BUFFER_SIZE
// # define BUFFER_SIZE 30
// # endif

typedef struct	s_sprxy
{
 	double		x; //position x du sprite
	double		y; //position y du sprite
}					t_sprxy;

typedef struct	s_sprite
{
	int			nbspr; //nombre de sprites
	int			*order;
	double		*dist;
	double 		spriteX;
    double 		spriteY;
	double 		invDet;
	double 		transformX;
    double 		transformY;
	int 		spriteScreenX;
	int 		spriteHeight;
	int			drawStartX;
	int 		drawStartY;
	int 		drawEndY;
	int 		drawEndX;
	int 		spriteWidth;
	double		*ZBuffer;
}					t_sprite;

typedef struct  s_texture
{
	int			texdir; //direction NO, S, EA, WE de la texture
	double		wallX; // valeur où le mur a été touché : coordonnée y si side == 0, coordonnée x si side == 1
	int			texX; // coordonnée x de la texture
	int			texY; // coordonée y de la texture
	double		step; // indique de combien augmenter les coordonnées de la texture pour chaque pixel
	double		texPos; // coordonnée de départ
}					t_texture;

typedef struct	s_ray
{
	double		posX;
	double		posY;
	double		dirX; //vecteur de direction
	double		dirY; //vecteur de direction
	double		planX; //vecteur du plan
	double		planY; //vecteur du plan
	double		rayDirX; //calcul de direction x du rayon
	double		rayDirY; //calcul de direction y du rayon
	double		cameraX; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	int			mapX; // coordonée x du carré dans lequel est pos
	int			mapY; // coordonnée y du carré dans lequel est pos
	double		sideDistX; //distance que le rayon parcours jusqu'au premier point d'intersection vertical
	double		sideDistY; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal
	double		deltaDistX; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltaDistY; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int			stepX; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int			stepY; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int			hit; // 1 si un mur a ete touche, 0 sinon
	int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpWallDist; // distance du rayon
	int			lineHeight; //hauteur de la ligne a dessiner
	int			drawStart; //position de debut ou il faut dessiner
	int			drawEnd; //position de fin ou il faut dessiner
	double		movespeed;
	double		rotspeed;
	int			x;
	int			texture;
}					t_ray;

typedef struct		s_data
{
//mlx, keys
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	int			minimapechelle;
	int			width; // recup->texture.width : nombre de pixels de largeur de la texture
	int 		height;// recup->texture.height : nombre de pixels dans la longueur de la texture
	void		*img2;
	int			*addr2;
}					t_data;

typedef struct		s_recup
{
//parsing :
	int			Rx;
	int			Ry;
	int			i;
	int			F;
	int			C;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	int			nblines;
	int			sizeline;
	char		**map;
	char		depart; //position depart : N S E W
	int			dx; //x de position depart
	int			dy; //y position depart
	int			indicateur;
	int			indicateur2;
	int			save;
	t_data		texture[5];
	t_data		data;
	t_ray		ray;
	t_texture	t;
	t_sprite	s;
	t_sprxy		*sxy;
}					t_recup;

//--------------PARSING----------------//
//parsing.c
int			ft_cub(char *str, t_recup *recup);
void		ft_parsing(char *fichier, t_recup *recup);
int			ft_parsing_map(char *fichier, t_recup *recup);
void		ft_imprime_map(t_recup *recup);
//parsing_utils.c
int			ft_strlen2(char *str);
int			ft_charinstr(char *str, char c);
int			ft_murs_util(char *str);
int			ft_depart(char c, t_recup *recup, int i, int j);
//parsing_color_resolution_texture.c
void		ft_color_resolution(char *str, t_recup *recup);
int			ft_atoi2(const char *str, t_recup *recup);
int			ft_atoi3(const char *str, t_recup *recup);
void    	ft_texture(char *str, t_recup *recup);
char		*ft_path_texture(char *str, t_recup *recup, int j);
//parsing_map.c
void		ft_initialisation(t_recup *recup);
int			ft_murs(t_recup *recup);
int			ft_is_map(char *str);
void		ft_map(char *str, t_recup *recup);
int			ft_copy_map(char *str, t_recup *recup);
void		ft_init_sprite(t_recup *recup);

//--------------RAYCASTING----------------//
//raycasting.c
int			ft_raycasting(t_recup *recup);
int			ft_mlx(t_recup *recup);
//keysdraw.c
int			ft_key_press(int keycode, t_recup *recup);
int			ft_key_release(int keycode, t_recup *recup);
int			ft_color_column(t_recup *recup);
void		ft_draw_texture(t_recup *recup, int x, int y);
//raycasting_init.c
void		ft_initialisation2(t_recup *recup);
void		ft_initialisation3(t_recup *recup);
void		ft_init_texture(t_recup *recup);
void		ft_init_sprite2(t_recup *recup, int i, int j, int v);
//raycasting_utils.c
void		ft_stepsideDist(t_recup *recup);
void		ft_incrementray(t_recup *recup);
void		ft_drawStartEnd(t_recup *recup);
void		ft_swap(t_recup *recup);
//raycasting_move.c
void		ft_forward_back(t_recup *recup);
void		ft_left_right(t_recup *recup);
void		ft_rotate_right_left(t_recup *recup);
//errors.c
void		ft_error(t_recup *recup, char *str);
int			ft_exit(t_recup *recup);
void		ft_verify_errors(t_recup *recup);
void		ft_header(t_recup *recup, int fd);
void		ft_save(t_recup *recup);
//--------------SPRITES----------------//
//sprites.c
void		ft_sprite(t_recup *recup);

//--------------BONUS----------------//
//minimap.c
int			ft_minimap(t_recup *recup);
void		my_color_cube(t_data *data, int x, int y, int color);
void		my_color_perso(t_data *data, int x, int y, int color);
//hitpoints.c
void		ft_hitpoints(t_recup *recup);


#endif
