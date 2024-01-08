/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:24:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/08 17:42:37 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppxb;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argc < 5)
	{
		ft_putstr_fd("Args number error\n", 2);
		exit(127);
	}
	ppxb = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppxb)
	{
		ft_putstr_fd("Allocation error\n", 2);
		exit(EXIT_FAILURE);
	}
	ppxb->pids = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	if (!ppxb->pids)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free(ppxb);
		exit(EXIT_FAILURE);
	}
	ppxb->pipes = (int **)malloc((argc - 4) * sizeof(int *));
	if (!ppxb->pipes)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free(ppxb);
		free(ppxb->pids);
		exit(EXIT_FAILURE);
	}
	while (i < argc - 4)
	{
		ppxb->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!ppxb->pipes[i])
		{
			ft_putstr_fd("Allocation error\n", 2);
			free(ppxb);
			free(ppxb->pids);
			while (j < i)
			{
				free(ppxb->pipes[j]);
				j++;
			}
			free(ppxb->pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ppxb->counter = 0;
	ft_pipex_bonus(ppxb, argv, envp, argc);
}
