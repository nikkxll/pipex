/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:27:10 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 23:02:45 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Prototype: void ft_putstr_fd(char *s, int fd);

// Turn in files: -

// Parameters s: The string to output.
// 			  fd: The file descriptor on which to write.

// Return value: None

// External functs.: write

// Description: Outputs the string ’s’ to the given file
// descriptor.

#include "../../headers/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		return ;
	}
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
	}
}
