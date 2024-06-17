Just like before the first thing we will do for all projects is add the header.
```
#include "so_long.h"
```

so the img.c only has 2 functions, one draws the image the other chooses what's the right image.
So let's start with the hard one.

```
t_block witch_block(char name)

{

    t_block map[6];

    int     i;

  

    map[0] = (t_block){"0", "./img/floor.xpm"};

    map[1] = (t_block){"1", "./img/water.xpm"};

    map[2] = (t_block){"C", "./img/plant.xpm"};

    map[3] = (t_block){"P", "./img/down.xpm"};

    map[4] = (t_block){"E", "./img/exit.xpm"};

    map[5] = (t_block){NULL, NULL};

    i = 0;

    while (map[i].name != NULL)

    {

        if (map[i].name[0] == name)

        {

            return (map[i]);

            break ;

        }

        i++;

    }

    return (map[5]);

}
```
This function maps a character name to a block type. It first initializes an array of [`t_block`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "mainfiles/so_long.h") structures, each of which represents a block type and consists of a character name and a path to an image file. It then iterates over the array until it finds a block with the same name as the input character, and returns that block. If it doesn't find a matching block, it returns the last block in the array, which has a NULL name and path. This function is used to determine the image that should be drawn for a particular cell on the game map.

This way we know that if P it prints player, C collectible, E exit, 0 floor and 1 wall.

```
void    *put_img(t_game *game, t_image image, int x, int y)

{

    image.img = mlx_xpm_file_to_image(image.wlx.mlx,

            image.path, &image.img_width, &image.img_heigth);

    if (!image.img)

        ft_error("Error xpm_file\n", game);

    mlx_put_image_to_window(image.wlx.mlx, image.wlx.window, image.img, x, y);

    mlx_destroy_image(image.wlx.mlx, image.img);

    return (image.img);

}
```
This function is responsible for drawing an image at a specific position on the game window. It first loads the image from the file specified in `image.path` using the `mlx_xpm_file_to_image` function. If the image fails to load, it calls [`ft_error`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "mainfiles/main.c") to print an error message and exit the program. It then draws the image at the position (x, y) on the window using the [`mlx_put_image_to_window`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "minilibx-linux/mlx_put_image_to_window.c") function. Finally, it destroys the image using the [`mlx_destroy_image`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "minilibx-linux/mlx_destroy_image.c") function to free the memory it occupies. The function returns the image that was drawn.

It's important to destroy the image so it doesn't cause memory leak problems.
Since the image is drawn it won't vanish from your screen.

