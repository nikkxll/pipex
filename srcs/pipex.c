/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:24:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/13 22:13:51 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	ft_pipex(t_pipex *ppx, char **av, char **env, int ac)
{
	int	status;
	int	pid_num;

	pid_num = -1;
	ppx->manual_path = "PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin";
	ppx->cmd_number = 2;
	piping(ppx, av, env, ac);
	while (pid_num++ < ppx->cmd_number - 2)
		waitpid(ppx->pids[pid_num], &status, 0);
	return (status >> 8);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("args number error\n", 2);
		exit(EXIT_FAILURE);
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
	free(ppx);
	free(ppx->pids);
	return (exit_status);
}
