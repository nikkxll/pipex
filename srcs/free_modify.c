/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_modify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:07 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/11 23:50:20 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	error(char *message, t_pipex *ppx, int error_num)
{
	ft_putstr_fd(message, 2);
	free(ppx);
	free(ppx->pids);
	exit(error_num);
}

void	error_cmd(char *message, t_pipex *ppx, int error_num)
{
	ft_putstr_fd(message, 2);
	if (ppx->cmd_args[0])
		ft_putendl_fd(ppx->cmd_args[0], 2);
	else
		ft_putchar_fd('\n', 2);
	free(ppx);
	free(ppx->pids);
	exit(error_num);
}

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
