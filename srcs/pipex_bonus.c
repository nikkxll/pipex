/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:24:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/07 22:50:12 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppxb;

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
	ppxb->commands = (int *)malloc((argc - 3) * sizeof(int));
	if (!ppxb->commands)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free(ppxb);
		exit(EXIT_FAILURE);
	}
	ppxb->counter = 0;
	ft_pipex_bonus(ppxb, argv, envp, argc);
}
