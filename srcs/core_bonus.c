/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 02:11:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

char	*get_env_path(char *cmd, char **envp, t_pipex *ppx, int i)
{
	char	**allpath;
	char	*path_part;
	char	*path_case;

	path_case = envp[if_path_exist(ppx, envp)];
	if (!ppx->path_flag)
		path_case = ppx->manual_path;
	allpath = ft_split(path_case + 5, ':');
	ppx->cmd_args = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		path_part = ft_strjoin(path_part, ppx->cmd_args[0]);
		if (access(path_part, F_OK | X_OK) == 0)
		{
			ft_free_split(allpath);
			return (path_part);
		}
		free(path_part);
	}
	ft_free_split(allpath);
	return (cmd);
}

void	exe_cmd(char *cmd, char **envp, t_pipex *ppx, int argc)
{
	char	*path;

	path = get_env_path(cmd, envp, ppx, -1);
	if (check_if_executable(ppx))
		execve(ppx->cmd_args[0], ppx->cmd_args, envp);
	if (execve(path, ppx->cmd_args, envp) == -1)
	{
		error_message_cmd(ppx, 127, argc);
		free(path);
	}
	ft_free_split(ppx->cmd_args);
}

void	create_pipes_and_exec(t_pipex *ppx, char *argv, char **envp, int argc)
{
	if (pipe(ppx->fd) == -1)
		exit(0);
	ppx->pids[ppx->cmd_number - 2] = fork();
	if (ppx->pids[ppx->cmd_number - 2] == -1)
		exit(0);
	if (!ppx->pids[ppx->cmd_number - 2])
	{
		if (dup2(ppx->fd[1], STDOUT_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		if (dup2(ppx->temp, STDIN_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		ppx->temp = ppx->fd[1];
		exe_cmd(argv, envp, ppx, argc);
	}
}

void	first(t_pipex *ppx, char *argv, char **envp, int argc, int file1_fd)
{
	// int fd[2];
	
	if (pipe(ppx->fd) == -1)
		exit(0);
	ppx->pids[ppx->cmd_number - 2] = fork();
	if (ppx->pids[ppx->cmd_number - 2] == -1)
		exit(0);
	if (!ppx->pids[ppx->cmd_number - 2])
	{
		if (dup2(file1_fd, STDIN_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		if (dup2(ppx->fd[1], STDOUT_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		close(ppx->fd[0]);
		close(file1_fd);
		ppx->temp = ppx->fd[1];
		exe_cmd(argv, envp, ppx, argc);
	}
	// close(ppx->fd[0]);
	// close(ppx->fd[1]);
}

void	last(t_pipex *ppx, char *argv, char **envp, int argc, int file2_fd)
{
	// int fd[2];
	
	if (ppx->cmd_number != 3)
	{
		if (pipe(ppx->fd) == -1)
			exit(0);
	}
	ppx->pids[ppx->cmd_number - 2] = fork();
	if (ppx->pids[ppx->cmd_number - 2] == -1)
		exit(0);
	if (!ppx->pids[ppx->cmd_number - 2])
	{
		if (dup2(file2_fd, STDOUT_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		if (dup2(ppx->temp, STDIN_FILENO) == -1)
			error("duplication error\n", ppx, 1, argc);
		close(ppx->fd[1]);
		close(file2_fd);
		exe_cmd(argv, envp, ppx, argc);
	}
	close(ppx->fd[0]);
	close(ppx->fd[1]);
}

void	ft_pipex_bonus(t_pipex *ppx, char **argv, char **envp, int argc)
{
	int	status;
	int	file1_fd;
	int	file2_fd;

	ppx->manual_path = "PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin";
	ppx->cmd_number = 2;
	first_file_validation(argv, ppx, argc);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		error("open file error\n", ppx, 1, argc);
	file2_fd = second_file_validation(argc, argv, ppx);
	first(ppx, argv[ppx->cmd_number], envp, argc, file1_fd);
	while (ppx->cmd_number < argc - 3)
	{
		ppx->cmd_number++;
		create_pipes_and_exec(ppx, argv[ppx->cmd_number], envp, argc);
	}
	ppx->cmd_number++;
	last(ppx, argv[ppx->cmd_number], envp, argc, file2_fd);
	while (ppx->cmd_number-- > 1)
	{
		// write(2, ft_itoa(ppx->cmd_number), ft_strlen(ft_itoa(ppx->cmd_number)));
		// waitpid(ppx->pids[ppx->cmd_number - 1], &status, 0);
		waitpid(ppx->pids[0], &status, 0);
		waitpid(ppx->pids[1], &status, 0);
		write(2, "1\n", 1);
		waitpid(ppx->pids[2], &status, 0);
	}
	exit(status >> 8);
}
