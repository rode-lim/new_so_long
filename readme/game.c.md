Just like before the first thing we will do for all projects is add the header.

```
#include "so_long.h"
```


This file is used for most of the functions that help with the player as well as making sure the game structure is well built.

```
void    destroy_map(t_game *game)

{

    int i;

  

    i = 0;

    while (game->map[i])

    {

        free(game->map[i]);

        i++;

    }

    free(game->map);

}
```
For example this function is responsible for freeing the memory allocated for the game map. It iterates over each row of the map and frees it, then it frees the map itself. This is typically used when the game is over or when an error occurs and the program needs to clean up before exiting.

This way we manage to prevent leaks in our game.

```
void    control_map(t_game *game)

{

    int i;

    int j;

  

    i = 0;

    while (game->map[i])

    {

        j = 0;

        while (game->map[i][j])

        {

            if (game->map[i][j] == 'E')

                game->exitcheck++;

            j++;

        }

        i++;

    }

    if (game->exitcheck != 1)

        ft_error("Error Exit check\n", game);

    if (game->coincheck == 0)

        ft_error("Error Coin check\n", game);

    if (game->playercheck != 1)

        ft_error("Error Player check\n", game);

}
```

While This function checks the validity of the game map. It iterates over each cell of the map and increments `game->exitcheck` each time it encounters an 'E' (exit). After checking all cells, it verifies that there is exactly one exit, at least one coin, and exactly one player on the map. If any of these conditions are not met, it calls `ft_error` to print an error message and exit the program.

This is important as in the subject it requires us to have at least 1 coin, exactly 1 exit and 1 player.
Anything else will result in failure of the project.

```
void    control_wall(t_game *game)

{

    size_t  x;

    int     y;

  

    y = 0;

    while (y < (game->size_y / 64))

    {

        x = 0;

        while (x < (game->size_x / 64))

        {

            if ((y == 0 || x == 0) && game->map[y][x] != '1')

                ft_error("Error Wall\n", game);

            else if ((y == (game->size_y / 64 - 1)

                    || x == (game->size_x / 64 - 1))

                && game->map[y][x] != '1')

                ft_error("Error Wall\n", game);

            x++;

        }

        y++;

    }

}
```
This function checks that the outer edges of the game map are all walls ('1'). It iterates over the first and last row and the first and last column of the map and checks that each cell is a wall. If it encounters a cell that is not a wall, it calls `ft_error` to print an error message and exit the program.

Again its required to be like this since the project states that all the walls should be walls.
This also prevents the player from moving away from the playable zone.

```
void    control_game(t_game *game)

{

    int j;

    int i;

  

    i = 0;

    j = 0;

    while (game->map[i])

    {

        j = 0;

        while (game->map[i][j])

        {

            if (game->map[i][j] == 'C')

                game->coincheck++;

            if (game->map[i][j] == 'P')

            {

                game->player.x = j * 64;

                game->player.y = i * 64;

                game->playercheck++;

            }

            j++;

        }

        i++;

    }

    control_map(game);

    control_wall(game);

    fill_flood(game);

}
```
This function initializes the game state and checks the validity of the game map. It iterates over each cell of the map, increments `game->coincheck` each time it encounters a 'C' (coin), and sets the player's position and increments `game->playercheck` each time it encounters a 'P' (player). After checking all cells, it calls `control_map` and `control_wall` to further validate the map, and `fill_flood` to initialize the flood fill algorithm used for path finding.

This means that all the previous functions displayed will be ran only after this one is ran.
Again if in this function it doesn't find a single coin, when control_map is called it will give an error based on the subject requirements.

```
int check_move(t_game *game, int i, int j)

{

    if (game->map[i][j] == '1')

        return (1);

    else if (game->map[i][j] == 'C')

    {

        game->player.coin++;

        game->map[i][j] = '0';

    }

    else if (game->map[i][j] == 'E')

    {

        if (game->player.coin != game->coincheck)

            return (1);

        window_destroy(game);

    }

    return (0);

}
```
This function checks if the player can move to the cell at (i, j). If the cell is a wall ('1'), it returns 1 to indicate that the move is not possible. If the cell is a coin ('C'), it increments the player's coin count, changes the cell to an empty cell ('0'), and returns 0 to indicate that the move is possible. If the cell is an exit ('E'), it checks if the player has collected all coins. If not, it returns 1 to indicate that the move is not possible. If all coins have been collected, it calls `window_destroy` to end the game and returns 0 to indicate that the move is possible. If the cell is neither a wall, a coin, nor an exit, it simply returns 0 to indicate that the move is possible.

Basically if I made the code a little to complex, it's still orienting towards a Y and X.
Whenever we move into a coin it replaces it with a empty space and updates the t_player struct in the coin variable to +1.
If the next move would be a wall, it returns 1 as it's not possible.
If the next move is an exit it checks if we have all coins and unless we do it still returns 1 as the movement is not possible.


