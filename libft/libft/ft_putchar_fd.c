/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:25:39 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 23:02:38 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Prototype: void ft_putchar_fd(char c, int fd);

// Turn in files: -

// Parameters: c: The character to output.
//			   fd: The file descriptor on which to write.

// Return value: None

// External functs.: write

// Description: Outputs the character ’c’ to the given file
// descriptor.

#include "../../headers/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
