/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/05 17:03:20 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_file_validation(char **argv, t_pipex *ppx)
{
	if (access(argv[1], F_OK) == -1)
		error_message("File doesn't exist", ppx, 1);
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error_message("Permission denied to the file 1", ppx, 1);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error_message("Open file error", ppx, 1);
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error_message("Permission denied to the file 2", ppx, 1);
	return (file2_fd);
}

void	check_if_executable(t_pipex *ppx, char **argv)
{
	ppx->cmd_args = ft_split(argv[ppx->cmd_number], ' ');
	if (access(ppx->cmd_args[0], X_OK) == 0)
		ppx->exec_flag = 1;
	else
		ppx->exec_flag = 0;
}

int	if_path_exist(t_pipex *ppx, char **envp)
{
	int	i;

	i = -1;
	ppx->path_flag = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			ppx->path_flag++;
			break ;
		}
	}
	return (i);
}
