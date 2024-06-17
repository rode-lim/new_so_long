```
#include "so_long.h"
```
First we include our header to be able to use most of the functions and to link files!
Then we must proceed to starting our main program!
As our project must be able to run independently by passing 2 arguments.

```
int	main(int ac, char **av)
{
    t_game	game;

    if (ac != 2)
        return (0);
    ft_window_size(&game, av);
    game.mlx = mlx_init();
    game.window = mlx_new_window(game.mlx, game.size_x, game.size_y, "so_long");
    start(&game);
    create_mapline(&game, av);
    control_game(&game);
    mlx_hook(game.window, 2, 1L, check_key, &game);
    mlx_hook(game.window, 17, 1L, window_destroy, &game);
    mlx_loop(game.mlx);
}
```
This is the main function of the program. It first checks if the number of command-line arguments is not 2, and if so, it returns 0 and ends the program. Then it sets the window size, initializes the MiniLibX library, creates a new window, and initializes the `game` struct. It then creates the map line, starts the game control, and sets up two hooks for key press and window close events. Finally, it starts the MiniLibX event loop.

So the next logical thing to do is to set the game struct to 0.
```
void	start(t_game *game)
{
    game->error = 0;
    game->coincheck = 0;
    game->exitcheck = 0;
    game->player.coin = 0;
    game->player.move = 0;
    game->playercheck = 0;
}
```
This function initializes the `game` struct by setting all its fields to 0.

Then we must have function that checks the key movements.
```
int	check_key(int keycode, t_game *game)
{
    if (keycode == 65307)
        window_destroy(game);
    if (keycode == 119)
        ft_up(game);
    if (keycode == 97)
        ft_left(game);
    if (keycode == 100)
        ft_right(game);
    if (keycode == 115)
        ft_down(game);
    return (0);
}
```
This function checks the keycode of a pressed key and performs an action based on the keycode. If the keycode is 65307, it destroys the game window. If the keycode is 119, 97, 100, or 115, it moves the player up, left, right, or down, respectively.

I also created 2 error functions in the main file.
One that will print a error and one that checks for a map error.
```
void	ft_error(char *msg, t_game *game)
{
    ft_printf("%s", msg);
    window_destroy(game);
    exit(1);
}
```
This function prints an error message, destroys the game window, and then exits the program with a status of 1, indicating an error.
```
void	ft_error_map(char *msg, t_game *game)
{
    if (game->error == 0)
        ft_printf("%s", msg);
    game->error++;
}
```
This function prints an error message if the `error` field of the `game` struct is 0, then increments the `error` field.

Following the order of the program the next file we will analyse will be the window.c as this is the first part of the main and the game.
We need to open a window and have it working!