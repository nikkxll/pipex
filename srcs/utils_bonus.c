/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/11 20:58:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	first_file_validation(char **argv, t_pipex *ppx, int argc)
{
	int	file1_fd;

	if (access(argv[1], F_OK) == -1)
		error_cmd("zsh: no such file or directory: ", ppx, 0, argc);
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error_cmd("zsh: permission denied: ", ppx, 1, argc);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		error("pipex: open file error\n", ppx, 1, argc);
	return (file1_fd);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error("pipex: open file error\n", ppx, 1, argc);
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error_cmd("zsh: permission denied: ", ppx, 1, argc);
	return (file2_fd);
}

int	check_if_executable(t_pipex *ppx, char *cmd, int argc)
{
	int	i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		while (cmd[i])
		{
			if (cmd[i] == ' ')
				error_cmd("zsh: permission denied: ", ppx, 0, argc);
			i++;
		}
	}
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
