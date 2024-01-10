/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:18:17 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/10 21:33:07 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		file1_fd;
	int		file2_fd;
	int		cmd_number;
	int		pipe_end[2];
	pid_t	child_1;
	pid_t	child_2;
	char	**all_paths_array;
	char	**cmd_args;
	char	*cmd;
	int		exec_flag;
	int		path_flag;
	char	*manual_path;
	char	*path_case;
}	t_pipex;

void	ft_pipex(t_pipex *ppx, char **argv, char **envp, int argc);
void	cmd_exe(t_pipex *ppx, char **argv, char **envp, int j);

void	error_message(char *message, t_pipex *ppx, int error_num);
void	error_message_cmd(t_pipex *ppx, int error_num);

void	first_file_validation(char **argv, t_pipex *ppx);
int		second_file_validation(int argc, char **argv, t_pipex *ppx);
int		if_path_exist(t_pipex *ppx, char **envp);
void	check_if_executable(t_pipex *ppx, char **argv);
void	free_splitted_path(char **split);
void	subs_tabs_on_spaces(char *str);

#endif
