#include "../inc/cub3d.h"

int		ft_atoi2(const char *str, t_recup *recup)
{
	int		signe;
	int		sum;

	sum = 0;
	signe = 1;
	while (str[recup->i] == ' ' || str[recup->i] == '\t'
			|| str[recup->i] == ',' || str[recup->i] == '\n'
			|| str[recup->i] == '\r' || str[recup->i] == '\v'
			|| str[recup->i] == '\f')
		recup->i++;
	if (str[recup->i] == '-' || str[recup->i] == '+')
	{
		if (str[recup->i] == '-')
			signe = -1;
		recup->i++;
	}
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
	{
		sum = (sum * 10) + (str[recup->i] - 48);
		recup->i++;
	}
	return (sum * signe);
}

int		ft_atoi3(const char *str, t_recup *recup)
{
	int		sum;

	sum = 0;
	while (str[recup->i] == ' ' || str[recup->i] == '\t'
			|| str[recup->i] == ',' || str[recup->i] == '\n'
			|| str[recup->i] == '\r' || str[recup->i] == '\v'
			|| str[recup->i] == '\f')
	{
		recup->i++;
		while (str[recup->i] >= '0' && str[recup->i] <= '9')
		{
			sum = (sum * 10) + (str[recup->i] - 48);
			recup->i++;
		}
	}
	return (sum);
}

char	*ft_path_texture(char *str, t_recup *recup)
{
	int		i;
	int		j;
	char	*copie;

	i = 0;
	j = 0;
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
			|| ft_strlen2(str) <= 2)
	{
		ft_error(recup, "Path texture invalide\n");
		return (NULL);
	}
	while (str[j] != '.')
		j++;
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
	int			i;
	static int	j = 0;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		recup->NO = ft_path_texture(str, recup);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		recup->SO = ft_path_texture(str, recup);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		recup->WE = ft_path_texture(str, recup);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		recup->EA = ft_path_texture(str, recup);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		recup->S = ft_path_texture(str, recup);
	j++;
}

//parse pour R F et C
void	ft_color_resolution(char *str, t_recup *recup)
{
	int			i;

	i = 0;
	recup->i = 1;
	if ((recup->sizeline > 0 || recup->nblines > 0) && (recup->NO == NULL
				|| recup->SO == NULL || recup->WE == NULL
				|| recup->EA == NULL || recup->S == NULL))
		ft_error(recup, "Map avant elements\n");
	while (str[i] != '\0')
	{
		if (str[i] == 'R')
		{
			if (recup->sizeline > 0 || recup->nblines > 0)
				ft_error(recup, "Map avant elements\n");
			recup->Rx = ft_atoi2(str, recup);
			recup->Ry = ft_atoi2(str, recup);
		}
		else if (str[i] == 'F')
		{
			if (recup->sizeline > 0 || recup->nblines > 0)
				ft_error(recup, "Map avant elements\n");
			recup->F = ft_atoi3(str, recup);
		}
		else if (str[i] == 'C')
		{
			if (recup->sizeline > 0 || recup->nblines > 0)
				ft_error(recup, "Map avant elements\n");
			recup->C = ft_atoi3(str, recup);
		}
		i++;
	}
}
