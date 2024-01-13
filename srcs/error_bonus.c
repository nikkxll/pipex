/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:07 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/13 21:52:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

void	ft_execve_fail(char *message, char *path, char *cmd, t_pipex *ppx)
{
	if (path != cmd)
		free(path);
	error_cmd(message, ppx, 127);
}

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
	ft_free_split(ppx->cmd_args);
	free(ppx);
	free(ppx->pids);
	exit(error_num);
}

void	error_file(char *message, char *file, t_pipex *ppx, int error_num)
{
	ft_putstr_fd(message, 2);
	if (file)
		ft_putendl_fd(file, 2);
	else
		ft_putchar_fd('\n', 2);
	free(ppx);
	free(ppx->pids);
	exit(error_num);
}
