/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/08 00:36:37 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

void	cmd_exe(t_pipex *ppx, char **argv, char **envp, int j, int argc)
{
	check_if_executable(ppx, argv);
	if (ppx->exec_flag == 1)
		execve(ppx->cmd_args[0], ppx->cmd_args, envp);
	else
	{
		ppx->path_case = envp[if_path_exist(ppx, envp)];
		if (!ppx->path_flag)
			ppx->path_case = ppx->manual_path;
		ppx->all_paths_array = ft_split(ppx->path_case + 5, ':');
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
	error_message_cmd(ppx, 127, argc);
}

void	child_process(t_pipex *ppxb, char *argv, char **envp, int argc)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_message("pipe error\n", ppxb, 1, argc);
	pid = fork();
	if (pid == -1)
		error_message("fork error\n", ppxb, 1, argc);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		cmd_exe(ppxb, &argv, envp, -1, argc);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		ppxb->commands[ppxb->counter] = pid;
		ppxb->counter++;
	}
}

void	last(t_pipex *ppxb, char *argv, char **envp, int argc)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_message("pipe error\n", ppxb, 1, argc);
	pid = fork();
	if (pid == -1)
		error_message("fork error\n", ppxb, 1, argc);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(ppxb->file2_fd , STDOUT_FILENO);
		cmd_exe(ppxb, &argv, envp, -1, argc);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		ppxb->commands[ppxb->counter] = pid;
		ppxb->counter++;
	}
}

void	ft_pipex_bonus(t_pipex *ppxb, char **argv, char **envp, int argc)
{
	int	status;
	int	i;

	ppxb->manual_path = "PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin";
	i = 2;
	ppxb->file2_fd = second_file_validation(argc, argv, ppxb);
	first_file_validation(argv, ppxb, argc);
	ppxb->file1_fd = open(argv[1], O_RDONLY);
	dup2(ppxb->file1_fd, STDIN_FILENO);
	while (i < argc - 2)
	{
		ppxb->cmd_number = i;
		child_process(ppxb, argv[i++], envp, argc);
	}
	last(ppxb, argv[argc - 2], envp, argc);
	while (ppxb->counter--)
		waitpid(ppxb->commands[ppxb->counter], &status, 0);
	while (1)
		continue ;
	exit(status >> 8);
}
