/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:44:46 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/13 22:01:28 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

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
