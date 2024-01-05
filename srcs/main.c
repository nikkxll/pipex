/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:03:04 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/05 16:37:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;

	if (argc != 5)
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
	ft_pipex(ppx, argv, envp, argc);
}
