#include "../inc/cub3d.h"

//renvoie 1 si la map n'est pas entouree de murs 0 si tout est ok
int		ft_murs(t_recup *recup)
{
	int i;

	i = 0;
	while (i < recup->nblines)
	{
		if (recup->map[i][0] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < recup->nblines)
	{
		if (recup->map[i][recup->sizeline - 1] != '1')
			return (1);
		i++;
	}
	if (ft_murs_util(recup->map[0]) == 1)
		return (1);
	if (ft_murs_util(recup->map[recup->nblines - 1]) == 1)
		return (1);
	return (0);
}

//copie str dans map
int		ft_copy_map(char *str, t_recup *recup)
{
	static int i = 0;
	int j;

	j = 0;
	recup->map[i] = NULL;
	if (!(recup->map[i] = malloc(sizeof(char) * recup->sizeline + 1)))
		return (0);
	while (str[j] != '\0')
	{
		if (ft_depart(str[j], recup, i, j) == 1)
			recup->map[i][j] = '0';
		else if (str[j] == ' ')
			recup->map[i][j] = '1';
		else
			recup->map[i][j] = str[j];
		j++;
	}
	while (j <= (recup->sizeline - 1))
	{
		recup->map[i][j] = '1';
		j++;
	}
	recup->map[i][j] = '\0';
	i++;
	return (0);
}

//check si la ligne fait partie de la map renvoie 1 si oui 0 sinon
int		ft_is_map(char *str)
{
	int i;

	i = 0;
	if (ft_charinstr(str, '1') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

//recupere nblines et sizeline
void	ft_map(char *str, t_recup *recup)
{
	int i;
	static int snblines = 0;
	static int ssizeline = 0;

	i = 0;
	if (ft_is_map(str) == 1)
	{
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	recup->nblines = snblines;
	recup->sizeline = ssizeline;
}
