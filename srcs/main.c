/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:03:04 by dnikifor          #+#    #+#             */
/*   Updated: 2024/01/03 17:20:33 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_message(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	first_file_validation(char **argv)
{
	if (access(argv[1], F_OK) == -1)
		error_message("File doesn't exist");
	if (access(argv[1], W_OK) == -1 || access(argv[1], R_OK) == -1)
		error_message("Permission denied to the file 1");
}

int	second_file_validation(int argc, char **argv)
{
	int	file2_fd;

	file2_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2_fd == -1)
		error_message("Open file error");
	if (access(argv[argc - 1], W_OK) == -1
		|| access(argv[argc - 1], R_OK) == -1)
		error_message("Permission denied to the file 2");
	return (file2_fd);
}

void	child_process(int f1, char **argv, int *end)
{
	if (dup2(f1, STDIN_FILENO) == -1)
		error_message("Duplication error for f1 stdin");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error_message("Duplication error for f1 stdout");
	close(end[0]);
	close(f1);
	execve();
	exit(EXIT_FAILURE);
}

void	parent_process(int f2, char **argv, int *end, pid_t parent)
{
	int	status;

	waitpid(parent, &status, 0);
	dup2(f2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(f2);
	execve();
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char **argv)
{
	int		pipe_end[2];
	pid_t	parent;

	if (pipe(pipe_end) == -1)
		error_message("Pipe error");
	parent = fork();
	if (parent < 0)
		error_message("Fork error");
	if (!parent)
		child_process(f1, argv, pipe_end);
	else
		parent_process(f2, argv, pipe_end, parent);
}

int	main(int argc, char **argv)
{
	int		file1_fd;
	int		file2_fd;
	int		pipefd[2];
	pid_t	pid;

	if (argc < 5)
		error_message("Args number error");
	first_file_validation(argv);
	file1_fd = open(argv[1], O_RDONLY);
	if (file1_fd == -1)
		error_message("Open file error");
	file2_fd = second_file_validation(argc, argv);
	pipex(file1_fd, file2_fd, argv);
	exit(EXIT_SUCCESS);
}
