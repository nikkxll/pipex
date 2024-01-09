/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:18:17 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/09 15:34:24 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		file1_fd;
	int		file2_fd;
	int		cmd_number;
	int		**pipes;
	char	**all_paths_array;
	char	**cmd_args;
	char	*cmd;
	int		exec_flag;
	int		path_flag;
	char	*manual_path;
	char	*path_case;
	pid_t	*pids;
	int		fd[2];
	int		counter;
	int		read_end;
}	t_pipex;

void	ft_pipex_bonus(t_pipex *ppxb, char **av, char **env, int ac);

void	error(char *message, t_pipex *ppx, int error_num, int argc);
void	error_message_cmd(t_pipex *ppx, int error_num, int argc);

void	first_file_validation(char **argv, t_pipex *ppx, int argc);
int		second_file_validation(int argc, char **argv, t_pipex *ppx);
int		if_path_exist(t_pipex *ppx, char **envp);
void	check_if_executable(t_pipex *ppx, char **argv);
void	free_splitted_path(char **split);

#endif
