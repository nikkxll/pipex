/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 12:26:05 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	first_file_validation(char **argv, t_pipex *ppx, int argc)
{
	int	file1_fd;
	
	if (access(argv[1], F_OK) == -1)
		error("pipex: input: No such file or directory\n", ppx, 1, argc);
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error("Permission denied to the file 1\n", ppx, 1, argc);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		error("Open file error\n", ppx, 1, argc);
	return (file1_fd);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error("Open file error\n", ppx, 1, argc);
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error("Permission denied to the file 2\n", ppx, 1, argc);
	return (file2_fd);
}

int	check_if_executable(t_pipex *ppx)
{
	if (ft_strncmp(ppx->cmd_args[0], "exit", 4) == 0)
		exit(ft_atoi(ppx->cmd_args[1]));
	if (access(ppx->cmd_args[0], X_OK) == 0)
		return (1);
	else
		return (0);
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

void	ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
