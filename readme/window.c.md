Just like before the first thing we will do for all projects is add the header.

```
#include "so_long.h"
```

Then we create the ft_window_size that we used in our main.

```
void	ft_window_size(t_game *data, char **av)
{
    int	fd;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        exit(1);
    if (ft_strnstr(av[1], ".ber", ft_strlen(av[1])) == NULL)
        exit(1);
    data->size_x = (ft_line(fd) * 64);
    data->size_y = (ft_count_line(fd) * 64);
    if (data->size_x == 0 || data->size_y == 0)
    {
        ft_printf("Mapa vazio\n");
        exit(1);
    }
}
```
This function sets the window size based on the dimensions of the game map. It opens the map file, checks if the file extension is ".ber", and then sets the [`size_x`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "mainfiles/so_long.h") and [`size_y`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "mainfiles/so_long.h") fields of the [`data`](vscode-file://vscode-app/c:/Users/ThisI/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "mainfiles/window.c") struct to the number of lines and the length of the longest line in the file, respectively, multiplied by 64. If either dimension is 0, it prints an error message and exits the program.

The reason we multiply by 64 its because every image/texture/sprite used in the project will have a ratio of 64x64 this way we can ensure the map will have enough space to print our window to run our project.

Now we make sure the project marks each location properly:
```
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
    }
    flood_fill(x + 1, y, flag, tab);
    flood_fill(x - 1, y, flag, tab);
    flood_fill(x, y + 1, flag, tab);
    flood_fill(x, y - 1, flag, tab);
}
```
This function performs a flood fill on the game map. It recursively checks each cell in the map and changes its value based on the current value. If the cell is a wall ('1') or has already been visited ('P'), it does nothing. If the cell is empty ('0') or contains a collectible ('C'), it marks it as visited. If the cell contains an exit ('E'), it increments the `flag` variable and leaves the cell as an exit.

Then we gotta check if our collectibles have been fully collected so that we can activate the exit:
```
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
```
This function checks if all collectibles in the game map have been collected. It iterates over each cell in the map and returns 0 if it finds a collectible.

We also create a flood_free to free the game map. This way we prevent some memory leaks:

```
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
```
Now we make a function that uses all of the previous ones in order to make sure the map is being well processed:
```
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
```
This function performs a flood fill on the game map starting from the player's position. It first creates a copy of the game map, then performs the flood fill in all four directions. After the flood fill, it checks if all collectibles have been collected and frees the memory allocated for the copy of the game map. If the flood fill did not reach an exit or there are still collectibles left, it prints an error message and exits the program.

