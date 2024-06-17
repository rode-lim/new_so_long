```
#include "so_long.h"
```
Like usual we start by adding the header.

Then lets move to the first function in map.c:

```
void    map_create(t_game *game, int i)

{

    int     j;

    t_image image;

    t_block map;

  

    image.wlx = *game;

    j = 0;

    while (game->map[i])

    {

        while (game->map[i][j])

        {

            map = witch_block(game->map[i][j]);

            image.path = map.path;

            put_img(game, image, (j * 64), (i * 64));

            j++;

        }

        i++;

    }

}
```
This function is used to create a map for the game. It iterates over the game's map array and for each character, it determines the corresponding block type using the `witch_block` function. It then sets the image path to the block's path and calls `put_img` to draw the image at the appropriate position on the screen.

```
void    floor_create(t_game *game, int i)

{

    int     j;

    t_image img;

  

    img.wlx = *game;

    j = 0;

    if (ft_strlen(game->map[i]) != game->size_x / 64

        && i != (game->size_y / 64))

        ft_error_map("Wrong map format\n", game);

    if (game->map[(game->size_y / 64)]

        && game->map[(game->size_y / 64)][0] != '\0')

        ft_error_map("Wrong map\n", game);

    while (game->map[i])

    {

        j = 0;

        while ((game->map[i][j]))

        {

            if (!ft_strchr("1PCE0", game->map[i][j]))

                ft_error("Error unrecognizable char\n", game);

            img.path = "./img/floor.xpm";

            put_img(game, img, (j * 64), (i * 64));

            j++;

        }

        i++;

    }

}
```
This function is used to create the floor of the game map. It first checks if the map is rectangular and if the last row of the map is empty. If not, it throws an error. Then it iterates over the game's map array and for each character, it checks if it's one of the allowed characters ("1PCE0"). If not, it throws an error. It then sets the image path to the floor image and calls `put_img` to draw the image at the appropriate position on the screen.

```
void    create_maplenght(char *area, t_game *game, int i)

{

    int     j;

  

    j = 0;

    game->map[i] = (char *)malloc(sizeof(char) * (game->size_x + 1));

    if (game->map[i] == NULL)

        return ;

    while (area[j] > 32)

    {

        if (area[j] == '\n')

            break ;

        game->map[i][j] = area[j];

        j++;

    }

    game->map[i][j] = '\0';

    free(area);

    floor_create(game, i);

    map_create(game, i);

}
```
This function is used to create a line of the game map. It first allocates memory for the line and then copies characters from the input string `area` to the map line until it encounters a newline character or a character with ASCII value less than or equal to 32 (space). It then calls `floor_create` and `map_create` to create the floor and map for the line.

The reason why we do this it's because I don't make the map in a single go, instead I first read 1 line and make that map for the first line, then I check the next line and make the map for it, hence and repeat until the map is finished.

I know there's people that read the entire map instantly but I found this to be the fastest and easiest way to learn.

```
void    create_mapline(t_game *game, char **av)

{

    int     fd;

    char    *area;

    int     i;

  

    i = 0;

    game->map = (char **)malloc(sizeof(char *) * (game->size_y + 1));

    if (game->map == NULL)

        return ;

    fd = open(av[1], O_RDONLY);

    while (i < game->size_y)

        game->map[i++] = 0;

    i = 0;

    while (i < game->size_y / 64)

    {

        area = get_next_line(fd);

        if (area == NULL)

            break ;

        create_maplenght(area, game, i);

        i++;

    }

    close(fd);

    if (game->error > 0)

        window_destroy(game);

}
```
So to make the previous function we must first make sure everything is fine! So we use create map line to read the entire file that is sent to us.

This function is used to create the entire game map. It first allocates memory for the map and then opens the file specified in `av[1]` for reading. It then reads lines from the file using `get_next_line` and calls `create_maplenght` to create a map line for each line read. If any errors occurred during the map creation, it calls `window_destroy` to clean up and exit the game.

```
int window_destroy(t_game *game)

{

    mlx_destroy_window(game->mlx, game->window);

    mlx_destroy_display(game->mlx);

    destroy_map(game);

    free(game->mlx);

    exit(1);

}
```
his function is used to clean up and exit the game. It destroys the game window and display, destroys the game map, frees the memory allocated for the game structure, and then exits the program with a status code of 1.