/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:03:04 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 22:59:12 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;

	if (argc < 5)
	{
		perror("Args number error");
		exit(EXIT_FAILURE);
	}
	ppx = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppx)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	first_file_validation(argv, ppx);
	ppx->file1_fd = open(argv[1], O_RDONLY);
	if (ppx->file1_fd == -1)
		error_message("Open file error", ppx);
	ppx->file2_fd = second_file_validation(argc, argv, ppx);
	ft_pipex(ppx, argv, envp);
	exit(EXIT_SUCCESS);
}
