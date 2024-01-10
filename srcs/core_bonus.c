/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 21:25:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

char	*get_env_path(char *cmd, char **env, t_pipex *ppx, int i)
{
	char	**path;
	char	*path_part;
	char	*path_case;

	path_case = env[if_path_exist(ppx, env)];
	if (!ppx->path_flag)
		path_case = ppx->manual_path;
	subs_tabs_on_spaces(cmd);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	path = ft_split(path_case + 5, ':');
	ppx->cmd_args = ft_split(cmd, ' ');
	while (path[++i])
	{
		path_part = ft_strjoin(path[i], "/");
		path_part = ft_strjoin(path_part, ppx->cmd_args[0]);
		if (access(path_part, F_OK | X_OK) == 0)
		{
			ft_free_split(path);
			return (path_part);
		}
		free(path_part);
	}
	ft_free_split(path);
	return (cmd);
}

void	execute_cmd(char *cmd, char **env, t_pipex *ppx, int ac)
{
	char	*path;

	path = get_env_path(cmd, env, ppx, -1);
	if (check_if_executable(ppx))
		execve(ppx->cmd_args[0], ppx->cmd_args, env);
	if (execve(path, ppx->cmd_args, env) == -1)
	{
		error_message_cmd(ppx, 127, ac);
		free(path);
	}
	ft_free_split(ppx->cmd_args);
}

void	child_execute(t_pipex *ppx, char **av, char **env, int ac)
{
	dup2(ppx->track_fd, STDIN_FILENO);
	if (ppx->cmd_number != ac - 2)
		dup2(ppx->fd[1], STDOUT_FILENO);
	else
	{
		ppx->last_fd = second_file_validation(ac, av, ppx);
		dup2(ppx->last_fd, STDOUT_FILENO);
	}
	close(ppx->fd[0]);
	execute_cmd(av[ppx->cmd_number], env, ppx, ac);
	exit(0);
}

void	piping(t_pipex *ppx, char **av, char **env, int ac)
{
	ppx->track_fd = -1;
	while (ppx->cmd_number < ac - 1)
	{
		if (pipe(ppx->fd) == -1)
			error("pipe error\n", ppx, 1, ac);
		ppx->pids[ppx->cmd_number - 2] = fork();
		if (ppx->pids[ppx->cmd_number - 2] == -1)
			error("fork error\n", ppx, 1, ac);
		else if (ppx->pids[ppx->cmd_number - 2] == 0)
		{
			if (ppx->cmd_number == 2)
				ppx->track_fd = first_file_validation(av, ppx, ac);
			child_execute(ppx, av, env, ac);
		}
		close(ppx->fd[1]);
		close(ppx->track_fd);
		ppx->track_fd = ppx->fd[0];
		ppx->cmd_number++;
	}
	close(ppx->fd[0]);
}

int	ft_pipex_bonus(t_pipex *ppx, char **av, char **env, int ac)
{
	int	status;
	int	pid_num;

	pid_num = -1;
	ppx->manual_path = "PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin";
	ppx->cmd_number = 2;
	piping(ppx, av, env, ac);
	while (pid_num++ < ppx->cmd_number - 2)
		waitpid(ppx->pids[pid_num], &status, 0);
	return (status >> 8);
}
