/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/09 15:40:56 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

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

char	*get_path(char *cmd, char **envp, t_pipex *ppx, int i)
{
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	allpath = ft_split(envp[if_path_exist(ppx, envp)], ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		path_part = ft_strjoin(path_part, s_cmd[0]);
		if (access(path_part, F_OK | X_OK) == 0)
		{
			ft_free_split(s_cmd);
			ft_free_split(allpath);
			return (path_part);
		}
		free(path_part);
	}
	ft_free_split(allpath);
	ft_free_split(s_cmd);
	return (cmd);
}

void	exe_cmd(char *cmd, char **env, t_pipex *ppx, int argc)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env, ppx, -1);
	if (execve(path, s_cmd, env) == -1)
	{
		free(path);
		ft_free_split(s_cmd);
		error_message_cmd(ppx, 127, argc);
	}
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
		close(ppx->fd[0]);
		dup2(ppx->fd[1], 1);
		exe_cmd(argv, envp, ppx, argc);
	}
	else
	{
		close(ppx->fd[1]);
		dup2(ppx->fd[0], 0);
	}
}

void	ft_pipex_bonus(t_pipex *ppx, char **argv, char **envp, int argc)
{
	int	status;

	ppx->cmd_number = 2;
	first_file_validation(argv, ppx, argc);
	ppx->file1_fd = open(argv[1], O_RDONLY);
	ppx->file2_fd = second_file_validation(argc, argv, ppx);
	dup2(ppx->file1_fd, STDIN_FILENO);
	while (ppx->cmd_number < argc - 2)
	{
		create_pipes_and_exec(ppx, argv[ppx->cmd_number], envp, argc);
		ppx->cmd_number++;
	}
	dup2(ppx->file2_fd, STDOUT_FILENO);
	exe_cmd(argv[argc - 2], envp, ppx, argc);
	while (ppx->cmd_number-- > 1)
		waitpid(ppx->pids[ppx->cmd_number - 2], &status, 0);
	// while (1)
	// 	continue ;
	exit(status >> 8);
}
