```
#include "so_long.h"
```
Like usual we start by adding the header.

Now moves is where we take in consideration how to move our character through the map.
Remembering tho that the check move function to make sure the move is valid is handled in game.c at the function check_move.

```
void    ft_up(t_game *game)

{

    int     i;

    int     j;

    t_image img;

  

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
```
This function moves the player up by one cell (64 pixels) if the move is valid. It first checks if the move is valid by calling `check_move`. If the move is valid, it increments the player's move count, updates the game state by calling `update`, updates the player's position, draws the player's image at the new position with the player facing up, and prints the new move count.

```
void    ft_down(t_game *game)

{

    int     i;

    int     j;

    t_image img;

  

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
```
This function is similar to `ft_up`, but it moves the player down by one cell (64 pixels) if the move is valid.

```
void    ft_left(t_game *game)

{

    int     i;

    int     j;

    t_image img;

  

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
```
This function is similar to `ft_up`, but it moves the player left by one cell (64 pixels) if the move is valid.

```
void    ft_right(t_game *game)

{

    int     i;

    int     j;

    t_image img;

  

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
```
 This function is similar to `ft_up`, but it moves the player right by one cell (64 pixels) if the move is valid.

All this functions work and are done the exact same way, as their objective is to update the image the true MVP of this functions is check_move that was explained before.

The most important function on this moves.c is update:

```
void    update(t_game *game, int x, int y)

{

    t_image img;

  

    img.path = "./img/floor.xpm";

    img.wlx = *game;

    put_img(game, img, game->player.x, game->player.y);

    put_img(game, img, x, y);

}
```
This function updates the game state by drawing a floor image at the current player position and at a new position specified by `x` and `y`. This is used to erase the player's image from the old position and draw a floor image at the new position before the player's image is drawn there.

This way we can make sure that the place we wore before is turned into a floor tile and that where the player is heading will turn into the player.