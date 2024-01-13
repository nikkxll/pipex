/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:44:29 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/13 22:11:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

char	*remove_backslashes(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	while (*src != '\0')
	{
		if (*src != '\\')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	return (dst);
}

void	subs(char *str)
{
	int	i;

	i = 0;
	str = remove_backslashes(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

void	loop_free(t_pipex *ppx, char *part)
{
	free(ppx->path_to_check);
	free(part);
}
