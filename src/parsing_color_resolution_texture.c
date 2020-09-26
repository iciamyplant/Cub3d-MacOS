#include "../inc/cub3d.h"

char	*ft_path_texture(char *str)
{
	int i;
	int j;
	char *copie;

	i = 0;
	j = 0;
	while (str[j] != '.')
	{
		j++;
		if (str[j] == '\0')
		{
			ft_error();
			return (NULL);
		}
	}
	if (!(copie = (malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		return (NULL);
	while (str[j] != '\0')
	{
		copie[i] = str[j];
		i++;
		j++;
	}
	copie[i] = '\0';
	return (copie);
}

//parse pour NO, SO, WE, EA, S
void	ft_texture(char *str, t_recup *recup)
{
	int i;
	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		recup->NO = ft_path_texture(str);
	if (str[i] == 'S' && str[i + 1] == 'O')
		recup->SO = ft_path_texture(str);
	if (str[i] == 'W' && str[i + 1] == 'E')
		recup->WE = ft_path_texture(str);
	if (str[i] == 'E' && str[i + 1] == 'A')
		recup->EA = ft_path_texture(str);
	if (str[i] == 'S' && str[i + 1] != 'O')
		recup->S = ft_path_texture(str);
}

//parse pour R F et C
void	ft_color_resolution(char *str, t_recup *recup)
{
	int			i;
	i = 0;
	recup->i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == 'R')
		{
			recup->Rx = ft_atoi2(str, recup);
			recup->Ry = ft_atoi2(str, recup);
		}
		else if (str[i] == 'F')
			recup->F = ft_atoi3(str, recup);
		else if (str[i] == 'C')
			recup->C = ft_atoi3(str, recup);
		i++;
	}
}
