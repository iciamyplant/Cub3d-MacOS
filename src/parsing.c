#include "../inc/cub3d.h"

void	ft_error(void)
{
	printf("y a une erreur\n");
}

//read une seconde fois pour recuperer la map
int		ft_parsing_map(char *fichier, t_recup *recup)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	if (!(recup->map = malloc(sizeof(char*) * recup->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (ft_is_map(str) == 1)
			ft_copy_map(str, recup);
		free(str);
	}
	close(fd);
	if (ft_murs(recup) == 1)
		write(1, "Error\nMap non entouree de 1\n", 28);
	ft_init_sprite(recup);
	ft_mlx(recup);
	return (0);
}

//read une premiere fois pour recuperer tout sauf la map +nblines +sizelines
void	ft_parsing(char *fichier)
{
	int			fd;
	int			ret;
	t_recup		recup;
	char		*str;

	ret = 1;
	str = NULL;
	ft_initialisation(&recup);
	fd = open(fichier, O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		ft_color_resolution(str, &recup);
		ft_texture(str, &recup);
		ft_map(str, &recup);
		free(str);
	}
	close(fd);
	ft_parsing_map(fichier, &recup);
}

//check si le fichier fichier finit bien par .cub
int		ft_cub(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			write(1, "Error\nNom de la map invalide\n", 29);
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str);
	else
		write(1, "Error\nNom de la map invalide\n", 29);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc >= 2)
		ft_cub(argv[1]);
	else
		write(1, "Error\nNombre d'arguments invalide\n", 35);
}
