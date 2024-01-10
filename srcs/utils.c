/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:52:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 21:32:36 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_file_validation(char **argv, t_pipex *ppx)
{
	if (access(argv[1], F_OK) == -1)
		error_message("pipex: input: No such file or directory\n", ppx, 0);
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error_message("Permission denied to the file 1\n", ppx, 1);
}

int	second_file_validation(int argc, char **argv, t_pipex *ppx)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error_message("Open file error\n", ppx, 1);
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error_message("Permission denied to the file 2\n", ppx, 1);
	return (file2_fd);
}

void	check_if_executable(t_pipex *ppx, char **argv)
{
	subs_tabs_on_spaces(argv[ppx->cmd_number]);
	if (access(argv[ppx->cmd_number], F_OK | X_OK) == 0)
	{
		ppx->exec_flag = 1;
		return ;
	}
	ppx->cmd_args = ft_split(argv[ppx->cmd_number], ' ');
	if (ft_strncmp(ppx->cmd_args[0], "exit", 4) == 0)
		exit(ft_atoi(ppx->cmd_args[1]));
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

void	free_splitted_path(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
