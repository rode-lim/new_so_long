/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rode-lim <rode-lim@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:00:30 by micarrel          #+#    #+#             */
/*   Updated: 2024/06/16 11:39:17 by rode-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update(t_game *game, int x, int y)
{
	t_image	img;

	img.path = "./img/floor.xpm";
	img.wlx = *game;
	put_img(game, img, game->player.x, game->player.y);
	put_img(game, img, x, y);
}

void	ft_up(t_game *game)
{
	int		i;
	int		j;
	t_image	img;

	img.path = "./img/up.xpm";
	img.wlx = *game;
	i = game->player.y - 64;
	j = game->player.x;
	if ((check_move(game, (i / 64), (j / 64)) != 1))
	{
		game->player.move++;
		update(game, j, i);
		game->player.y = i;
		game->player.x = j;
		put_img(game, img, j, i);
		ft_printf("Moves: %d\n", game->player.move);
	}
}

void	ft_down(t_game *game)
{
	int		i;
	int		j;
	t_image	img;

	img.path = "./img/down.xpm";
	img.wlx = *game;
	i = game->player.y + 64;
	j = game->player.x;
	if ((check_move(game, (i / 64), (j / 64)) != 1))
	{
		game->player.move++;
		update(game, j, i);
		game->player.y = i;
		game->player.x = j;
		put_img(game, img, j, i);
		ft_printf("Moves: %d\n", game->player.move);
	}
}

void	ft_left(t_game *game)
{
	int		i;
	int		j;
	t_image	img;

	img.path = "./img/left.xpm";
	img.wlx = *game;
	i = game->player.y;
	j = game->player.x - 64;
	if ((check_move(game, (i / 64), (j / 64)) != 1))
	{
		game->player.move++;
		update(game, j, i);
		game->player.y = i;
		game->player.x = j;
		put_img(game, img, j, i);
		ft_printf("Moves: %d\n", game->player.move);
	}
}

void	ft_right(t_game *game)
{
	int		i;
	int		j;
	t_image	img;

	img.path = "./img/right.xpm";
	img.wlx = *game;
	i = game->player.y;
	j = game->player.x + 64;
	if ((check_move(game, (i / 64), (j / 64)) != 1))
	{
		game->player.move++;
		update(game, j, i);
		game->player.y = i;
		game->player.x = j;
		put_img(game, img, j, i);
		ft_printf("Moves: %d\n", game->player.move);
	}
}
