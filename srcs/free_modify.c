/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_modify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:07 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 21:32:59 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	error_message(char *message, t_pipex *ppx, int error_num)
{
	ft_putstr_fd(message, 2);
	if (ppx->cmd_number == 3)
		free(ppx);
	exit(error_num);
}

void	error_message_cmd(t_pipex *ppx, int error_num)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(ppx->cmd_args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (ppx->cmd_number == 3)
		free(ppx);
	exit(error_num);
}

void	subs_tabs_on_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
