/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:24:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/11 21:03:55 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("args number error\n", 2);
		exit(127);
	}
	ppx = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppx)
	{
		ft_putstr_fd("allocation error\n", 2);
		exit(EXIT_FAILURE);
	}
	ppx->pids = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	if (!ppx->pids)
	{
		ft_putstr_fd("allocation error\n", 2);
		free(ppx);
		exit(EXIT_FAILURE);
	}
	exit_status = ft_pipex(ppx, argv, envp, argc);
	exit (exit_status);
}
