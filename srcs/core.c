/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 23:24:38 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	cmd_exe(t_pipex *ppx, char **argv, char **envp, int cmd_number)
{
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break;
	}
	ppx->all_paths_array = ft_split(envp[i], ':');
	ppx->cmd_args = ft_split(argv[cmd_number], ' ');
	while (ppx->all_paths_array[++j])
	{
		cmd = ft_strjoin(ppx->all_paths_array[j], "/");
		cmd = ft_strjoin(cmd, ppx->cmd_args[0]);
		execve(cmd, ppx->cmd_args, envp);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

void	child_process(t_pipex *ppx, char **argv, char **envp)
{
	if (dup2(ppx->file1_fd, STDIN_FILENO) == -1)
		error_message("Duplication error for f1 stdin", ppx);
	if (dup2(ppx->pipe_end[1], STDOUT_FILENO) == -1)
		error_message("Duplication error for f1 stdout", ppx);
	close(ppx->pipe_end[0]);
	close(ppx->file1_fd);
	ppx->cmd_number = 2;
	cmd_exe(ppx, argv, envp, ppx->cmd_number);
	exit(EXIT_FAILURE);
}

void	parent_process(t_pipex *ppx, char **argv, char **envp)
{
	int	status;

	waitpid(ppx->child_1, &status, 0);
	dup2(ppx->file2_fd, STDOUT_FILENO);
	dup2(ppx->pipe_end[0], STDIN_FILENO);
	close(ppx->pipe_end[1]);
	close(ppx->file2_fd);
	ppx->cmd_number = 3;
	cmd_exe(ppx, argv, envp, ppx->cmd_number);
	exit(EXIT_FAILURE);
}

void	ft_pipex(t_pipex *ppx, char **argv, char **envp)
{
	if (pipe(ppx->pipe_end) == -1)
		error_message("Pipe error", ppx);
	ppx->child_1 = fork();
	if (ppx->child_1 < 0)
		error_message("Fork error", ppx);
	if (!ppx->child_1)
		child_process(ppx, argv, envp);
	else
		parent_process(ppx, argv, envp);
}
