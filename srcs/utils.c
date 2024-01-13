/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/13 22:11:28 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	first_file_validation(char **argv, t_pipex *ppx)
{
	int	file1_fd;

	if (access(argv[1], F_OK) == -1)
		error_file("zsh: no such file or directory: ", argv[1], ppx, 0);
	if (access(argv[1], R_OK) == -1)
		error_file("zsh: permission denied: ", argv[1], ppx, 1);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		error_file("pipex: open file error: ", argv[1], ppx, 1);
	return (file1_fd);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) == -1)
		error_file("zsh: permission denied: ", argv[argc - 1], ppx, 1);
	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error_file("pipex: open file error: ", argv[argc - 1], ppx, 1);
	return (file2_fd);
}

int	check_if_executable(t_pipex *ppx, char *cmd, char *path)
{
	int	i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		while (cmd[i])
		{
			if (cmd[i] == ' ')
			{
				if (path != cmd)
					free(path);
				error_cmd("zsh: permission denied: ", ppx, 0);
			}
			i++;
		}
	}
	if (ppx->cmd_args[0] && ft_strncmp(ppx->cmd_args[0], "exit", 4) == 0)
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
