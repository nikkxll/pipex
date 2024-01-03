/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:36:45 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 23:01:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SYNOPSIS
//	#include <stdlib.h>
//	void *calloc(size_t count, size_t size);

// DESCRIPTION
//	The calloc() function contiguously allocates enough space for 
//	count objects that are size bytes of memory each and
//	returns a pointer to the allocated memory.  
//	The allocated memory is filled with bytes of value zero.

// RETURN VALUES
//	If successful, calloc(), malloc(), realloc(), reallocf(), and valloc() 
//	functions return a pointer to allocated memory.  
//	If there is an error, they return a NULL pointer and set errno to ENOMEM.

#include "../../headers/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	max;

	max = 4611686014132420608;
	if (!size || !count)
		return (ft_calloc(1, 1));
	if (size && count && (max / size < count))
		return (0);
	p = (void *)malloc(count * size * sizeof(void));
	if (!p)
		return (0);
	ft_memset(p, '\0', count * size);
	return (p);
}
