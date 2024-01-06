/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:07 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/06 13:09:10 by dnikifor         ###   ########.fr       */
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
