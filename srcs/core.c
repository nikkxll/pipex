/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/06 14:40:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	cmd_exe(t_pipex *ppx, char **argv, char **envp, int i)
{
	int		j;

	j = -1;
	check_if_executable(ppx, argv);
	if (ppx->exec_flag == 1)
		execve(ppx->cmd_args[0], ppx->cmd_args, envp);
	else
	{
		i = if_path_exist(ppx, envp);
		if (!ppx->path_flag)
			error_message("No such file or directory\n", ppx, 0);
		ppx->all_paths_array = ft_split(envp[i] + 5, ':');
		if (ppx->all_paths_array[0])
		{
			while (ppx->all_paths_array[++j])
			{
				ppx->cmd = ft_strjoin(ppx->all_paths_array[j], "/");
				ppx->cmd = ft_strjoin(ppx->cmd, ppx->cmd_args[0]);
				if (execve(ppx->cmd, ppx->cmd_args, envp) == -1)
					free(ppx->cmd);
			}
		}
	}
	free_splitted_path(ppx->all_paths_array);
	error_message_cmd(ppx, 127);
}

void	child_process_1(t_pipex *ppx, char **argv, char **envp)
{
	first_file_validation(argv, ppx);
	ppx->file1_fd = open(argv[1], O_RDONLY);
	if (ppx->file1_fd == -1)
		error_message("open file error\n", ppx, 1);
	if (dup2(ppx->file1_fd, STDIN_FILENO) == -1)
		error_message("duplication error for f1 stdin\n", ppx, 1);
	if (dup2(ppx->pipe_end[1], STDOUT_FILENO) == -1)
		error_message("duplication error for f1 stdout\n", ppx, 1);
	close(ppx->pipe_end[0]);
	ppx->cmd_number = 2;
	cmd_exe(ppx, argv, envp, -1);
}

void	child_process_2(t_pipex *ppx, char **argv, char **envp, int argc)
{
	ppx->file2_fd = second_file_validation(argc, argv, ppx);
	if (dup2(ppx->file2_fd, STDOUT_FILENO) == -1)
		error_message("duplication error for f2 stdout\n", ppx, 1);
	if (dup2(ppx->pipe_end[0], STDIN_FILENO) == -1)
		error_message("duplication error for f2 stdin\n", ppx, 1);
	close(ppx->pipe_end[1]);
	ppx->cmd_number = 3;
	cmd_exe(ppx, argv, envp, -1);
}

void	ft_pipex(t_pipex *ppx, char **argv, char **envp, int argc)
{
	int	status;

	if (pipe(ppx->pipe_end) == -1)
		error_message("pipe error\n", ppx, 1);
	ppx->child_1 = fork();
	if (ppx->child_1 < 0)
		error_message("fork error\n", ppx, 1);
	if (!ppx->child_1)
		child_process_1(ppx, argv, envp);
	ppx->child_2 = fork();
	if (ppx->child_2 < 0)
		error_message("fork error\n", ppx, 1);
	if (!ppx->child_2)
		child_process_2(ppx, argv, envp, argc);
	close(ppx->pipe_end[0]);
	close(ppx->pipe_end[1]);
	waitpid(ppx->child_1, &status, 0);
	waitpid(ppx->child_2, &status, 0);
	exit (status >> 8);
}
