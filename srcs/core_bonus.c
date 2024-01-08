/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:53:42 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/08 18:28:16 by dnikifor         ###   ########.fr       */
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

void child_process(int in_fd, int out_fd)
{
    dup2(in_fd, STDIN_FILENO);
    dup2(out_fd, STDOUT_FILENO);

    close(in_fd);
    close(out_fd);
}

void	ft_pipex_bonus(t_pipex *ppxb, char **argv, char **envp, int argc)
{
	int	status;
	int	i;
	int	j;
	char buffer[1000];
	int n;

	i = 0;
	j = 0;

	ppxb->manual_path = "PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin";
	ppxb->cmd_number = 2;

	first_file_validation(argv, ppxb, argc);
	ppxb->file1_fd = open(argv[1], O_RDONLY);
	ppxb->file2_fd = second_file_validation(argc, argv, ppxb);

	while (i != argc - 4)
	{
		if (pipe(ppxb->pipes[i]) == -1)
		{
			perror("pipe error");
			exit (1);
		}
		i++;
	}
	
	while (j < argc - 3)
	{
		ppxb->pids[j] = fork();
		if (ppxb->pids[j] == 0)
		{
			if (j == 0)
			{
				ppxb->cmd_number = j + 2;
				ppxb->counter++;
				child_process(ppxb->file1_fd, ppxb->pipes[j][1]);
				cmd_exe(ppxb, argv, envp, -1, argc);
			}
			else if (j == argc - 4)
			{
				ppxb->cmd_number = j + 2;
				ppxb->counter++;
				child_process(ppxb->pipes[j - 1][0], ppxb->file2_fd);
				cmd_exe(ppxb, argv, envp, -1, argc);
			}
			else
			{
				ppxb->cmd_number = j + 2;
				ppxb->counter++;
				child_process(ppxb->pipes[j - 1][0], ppxb->pipes[j][1]);
				n = read(STDIN_FILENO, buffer, 1000);
				write(2, buffer, ft_strlen(buffer));
				write(2, "\n\n", 2);
				cmd_exe(ppxb, argv, envp, -1, argc);
			}
		}
		j++;
	}
	 for (int k = 0; k < 2; ++k)
	 {
		close(ppxb->pipes[k][0]);
		close(ppxb->pipes[k][1]);
	}
	while (ppxb->counter--)
		waitpid(ppxb->pids[ppxb->counter], &status, 0);
	while (1)
		continue ;
	exit(status >> 8);
}
