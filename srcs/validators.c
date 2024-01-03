/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 23:10:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_file_validation(char **argv, t_pipex *ppx)
{
	if (access(argv[1], F_OK) == -1)
		error_message("File doesn't exist", ppx);
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error_message("Permission denied to the file 1", ppx);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error_message("Open file error", ppx);
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error_message("Permission denied to the file 2", ppx);
	return (file2_fd);
}
