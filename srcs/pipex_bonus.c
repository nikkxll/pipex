/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:24:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 13:42:17 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		exit_status;

	if (argc < 5)
	{
		ft_putstr_fd("Args number error\n", 2);
		exit(127);
	}
	ppx = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppx)
	{
		ft_putstr_fd("Allocation error\n", 2);
		exit(EXIT_FAILURE);
	}
	ppx->pids = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	if (!ppx->pids)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free(ppx);
		exit(EXIT_FAILURE);
	}
	exit_status = ft_pipex_bonus(ppx, argv, envp, argc);
	exit (exit_status);
}
