/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_modify_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:07 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 21:15:00 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

void	error(char *message, t_pipex *ppx, int error_num, int argc)
{
	ft_putstr_fd(message, 2);
	if (ppx->cmd_number == argc - 2)
		free(ppx);
	free(ppx->pids);
	exit(error_num);
}

void	error_message_cmd(t_pipex *ppx, int error_num, int argc)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(ppx->cmd_args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (ppx->cmd_number == argc - 2)
		free(ppx);
	free(ppx->pids);
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
