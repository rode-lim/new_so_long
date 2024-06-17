/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rode-lim <rode-lim@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:29:01 by micarrel          #+#    #+#             */
/*   Updated: 2024/06/16 17:40:10 by rode-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_line(int fd)
{
	char	buffer;
	int		length;
	int		bytes;

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

int	ft_count_line(int fd)
{
	int		linecount;
	char	buffer;
	int		bytes;

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

void	*myfree(void *str)
{
	free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	*line;
	int		rd_byte;
	int		i;

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
