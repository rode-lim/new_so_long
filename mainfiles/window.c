/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rode-lim <rode-lim@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:39:33 by rode-lim          #+#    #+#             */
/*   Updated: 2024/06/16 11:39:33 by rode-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_window_size(t_game *data, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
	if (ft_strnstr(av[1], ".ber", ft_strlen(av[1])) == NULL)
	{
		ft_printf("Error\n");
		exit(1);
	}
	data->size_x = (ft_line(fd) * 64);
	data->size_y = (ft_count_line(fd) * 64);
	if (data->size_x == 0 || data->size_y == 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
}

void	flood_fill(int x, int y, int *flag, char **tab)
{
	if (tab[y][x] == '1' || tab[y][x] == 'P')
		return ;
	else if (tab[y][x] == '0')
		tab[y][x] = 'P';
	else if (tab[y][x] == 'C')
		tab[y][x] = 'P';
	else if (tab[y][x] == 'E')
	{
		(*flag)++;
		tab[y][x] = 'E';
		return ;
	}
	flood_fill(x + 1, y, flag, tab);
	flood_fill(x - 1, y, flag, tab);
	flood_fill(x, y + 1, flag, tab);
	flood_fill(x, y - 1, flag, tab);
}

int	check_all_collectible(char **temp)
{
	int	x;
	int	y;

	y = 0;
	while (temp[y])
	{
		x = 0;
		while (temp[y][x])
		{
			if (temp[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	flood_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	fill_flood(t_game *game)
{
	int		x;
	int		y;
	int		flag;
	char	**tab;
	int		i;

	flag = 0;
	x = game->player.x;
	y = game->player.y;
	tab = malloc(sizeof(char **) * (game->size_y + 1));
	i = 0;
	while (game->map[i])
	{
		tab[i] = ft_strdup(game->map[i]);
		i++;
	}
	tab[i] = '\0';
	flood_fill(x / 64 + 1, y / 64, &flag, tab);
	flood_fill(x / 64 - 1, y / 64, &flag, tab);
	flood_fill(x / 64, y / 64 - 1, &flag, tab);
	flood_fill(x / 64, y / 64 + 1, &flag, tab);
	i = check_all_collectible(tab);
	flood_free(tab);
	if (flag == 0 || !i)
		ft_error("Exit Error\n", game);
}
