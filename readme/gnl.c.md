Just like before the first thing we will do for all projects is add the header.

```
#include "so_long.h"
```

Now let's analyse this project get_next_line as we use it to open the .ber file.

What's the difference between this get_next_line and a normal one?
The difference between this version of `get_next_line` and a typical one is that a typical `get_next_line` function reads a line from a file and leaves the file pointer at the start of the next line, so that subsequent calls to `get_next_line` will read subsequent lines. This version of `get_next_line`, however, reads the entire file in one go and returns the entire contents as a single string. This is because it doesn't stop reading when it encounters a newline character, but continues reading until it reaches the end of the file.

```
char    *get_next_line(int fd)

{

    char    buffer;

    char    *line;

    int     rd_byte;

    int     i;

  

    rd_byte = 1;

    i = 0;

    line = (char *)malloc(sizeof(char) * (9999));

    buffer = 0;

    if (fd < 0)

        return (NULL);

    while (rd_byte > 0)

    {

        rd_byte = read(fd, &buffer, 1);

        if (rd_byte <= 0)

            break ;

        line[i++] = buffer;

        if (buffer == '\n')

            break ;

    }

    line[i] = '\0';

    if (!*line)

        myfree(line);

    return (line);

}
```

This function reads characters from a file descriptor `fd` one by one and stores them in a buffer until it encounters a newline character or reaches the end of the file. It then null-terminates the buffer and returns it as a string. If the string is empty, it frees the memory and returns NULL. This function is used to read a line from a file.

We free the project with my free:
```
void    *myfree(void *str)

{

    free(str);

    return (NULL);

}
```
This function frees the memory pointed to by `str` and returns NULL. It's a utility function used to free memory and nullify the pointer in one step.


```
int ft_count_line(int fd)

{

    int     linecount;

    char    buffer;

    int     bytes;

  

    buffer = 0;

    linecount = 1;

    while (1)

    {

        bytes = read(fd, &buffer, 1);

        if (bytes < 1)

            break ;

        if (buffer == '\n')

            linecount++;

    }

    if (buffer == '1')

        linecount++;

    return (linecount);

}
```
Just like the name of the function says, we count lines.
This function reads characters from a file descriptor `fd` one by one and increments a counter each time it encounters a newline character. If the last character read is '1', it increments the counter one more time. It returns the total count of lines in the file. This function is used to count the number of lines in a file.

```
int ft_line(int fd)

{

    char    buffer;

    int     length;

    int     bytes;

  

    buffer = 0;

    bytes = 1;

    length = 0;

    while (bytes == 1)

    {

        bytes = read(fd, &buffer, 1);

        if (buffer != '\n')

            length++;

        else

            break ;

    }

    return (length);

}
```
This function reads characters from a file descriptor `fd` one by one until it encounters a newline character ('\n'). It returns the number of characters read (not including the newline character). This function is used to determine the length of a line in a file.

This way this function stores what's a line and what's in it.