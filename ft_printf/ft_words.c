/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rode-lim <rode-lim@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:01:33 by rode-lim          #+#    #+#             */
/*   Updated: 2024/06/16 11:40:36 by rode-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char chr, int *len)
{
	write(1, &chr, 1);
	(*len)++;
}

void	ft_putstr(char *args, int *len)
{
	size_t	i;

	i = 0;
	if (args == 0)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (args[i] != '\0')
	{
		ft_putchar(args[i], len);
		i++;
	}
}
