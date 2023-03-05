/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:17:36 by atoof             #+#    #+#             */
/*   Updated: 2023/03/05 13:42:56 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*get_cmd is a static function that takes in an array
of paths and a command, and returns a pointer to a string
,temp is a pointer to a string that will be used to
temporarily store a concatenation of a path and a "/"
,unix_cmd is a pointer to a string that will be used to
temporarily store a concatenation of a path, a "/", and a command
if no valid command is find, return null*/
/*line47:redirect stdout to the write end of the pipe*/
/*line48: close the read end of the pipe*/
/*line49: redirects the standard input to the file descriptor pipex.infile.
This can be used to redirect the input of a command or process to come from
a pipe or file instead of the keyboard*/

// static char	*get_cmd(char **path, char *cmd)
// {
// 	char	*temp;
// 	char	*unix_cmd;

// 	printf("cmd is %s\n", cmd);
// 	while (*path)
// 	{
// 		temp = ft_strjoin(*path, "/");
// 		unix_cmd = ft_strjoin(temp, cmd);
// 		free(temp);
// 		if (access(unix_cmd, 0) == 0)
// 		{
// 			return (unix_cmd);
// 		}
// 		free(unix_cmd);
// 		path++;
// 	}
// 	return (NULL);
// }
static char	*get_cmd(char **path, char *cmd)
{
	char		*temp;
	char		*unix_cmd;
	//struct stat	statbuf;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		unix_cmd = ft_strjoin(temp, cmd);
		free(temp);
		//if (stat(unix_cmd, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
		if (access(unix_cmd, X_OK) == 0)
		{
			return (unix_cmd);
		}
		free(unix_cmd);
		path++;
	}
	return (NULL);
}
// void	child1(t_pipex *pipex, char *argv[], char *envp[])
// {
// 	// if ((pipex->infile = open(argv[1], O_RDONLY)) < 0)
// 	// 	error("INFILE", pipex);
// 	if (!(pipex->cmd_arguments = ft_split(argv[2], ' ')))
// 		error("CMD1_ARGUMENT", pipex);
// 	// printf("cmd arguments %s\n", pipex->cmd_arguments[0]);
// 	// printf("cmd arguments %s\n", pipex->cmd_arguments[1]);
// 	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_arguments[0]);
// 	// printf("%s\n", pipex->cmd);
// 	if (!pipex->cmd)
// 	{
// 		// free_child(&pipex);
// 		write(1, "here\n", 5);
// 		error("CMD1", pipex);
// 		close(pipex->infile);
// 		// ft_putstr_fd("zsh: command not found: ", 2);
// 		// ft_putstr_fd(argv[2], 2);
// 		// ft_putstr_fd("\n", 2);
// 		// exit(1);
// 	}
// 	if (dup2(pipex->end[FD_WRITE_END], STDOUT_FILENO) < 0)
// 		error("child 1, first DUP2", pipex);
// 	if ((dup2(pipex->infile, STDIN_FILENO)) < 0)
// 		error("child 1, second DUP2", pipex);
// 	// close(pipex->end[FD_READ_END]);
// 	close(pipex->end[FD_WRITE_END]);
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	if (execve(pipex->cmd, pipex->cmd_arguments, envp) == -1)
// 	{
// 		error("EXECVE1", pipex);
// 		// close(pipex->infile);
// 	}
// }

void	child1(t_pipex *pipex, char *argv[], char *envp[])
{
	//add by lin
	if (!(pipex->cmd_arguments = ft_split(argv[2], ' ')))
		error("CMD1_ARGUMENT", pipex);
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_arguments[0]);
	if (!pipex->cmd)
		error("COMMAND1", pipex); // command not found
	// lin: why create outfile twice??
	//if ((pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
	//		0644)) < 0)
	//	error("OUTFILE", pipex);
	dup2(pipex->infile, STDIN_FILENO);
	//dup2(pipex->outfile, STDOUT_FILENO);
	//add by Lin
	dup2(pipex->end[1], STDOUT_FILENO);
	//3 lines add by lin
	close(pipex->end[FD_WRITE_END]);
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->end[FD_READ_END]);
	// if inflie doesnot exist, let's return after we close all the fds.
	if (pipex->infile < 0)
		return;
	execve(pipex->cmd, pipex->cmd_arguments, envp);
}

// void	child2(t_pipex *pipex, char **argv, char **envp)
// {
// 	if ((pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644)) < 0)
// 		error("OUTFILE", pipex);
// 	printf("%d - %d - %d - %d\n", pipex->infile, pipex->outfile, pipex->end[0],
// 		pipex->end[1]);
// 	if (!(pipex->cmd_arguments = ft_split(argv[3], ' ')))
// 		error("CMD2_ARGUMENT", pipex);
// 	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_arguments[0]);
// 	printf("%s\n", pipex->cmd_arguments[0]);
// 	printf("%s\n", pipex->cmd);
// 	if (!pipex->cmd)
// 	{
// 		// free_pipex(&pipex);
// 		error("CMD2", pipex);
// 		close(pipex->outfile);
// 		// ft_putstr_fd("zsh: command not found: ", 2);
// 		// ft_putstr_fd(argv[3], 2);
// 		// ft_putstr_fd("\n", 2);
// 		// exit(EXIT_FAILURE);
// 	}
// 	// if (dup2(pipex->end[FD_READ_END], STDIN_FILENO) < 0)
// 	// 	error("DUP2", pipex);
// 	// if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
// 	// 	error("DUP2", pipex);
// 	dup2(pipex->end[FD_READ_END], STDIN_FILENO);
// 	dup2(pipex->outfile, STDOUT_FILENO);
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	// close(pipex->end[FD_WRITE_END]);
// 	close(pipex->end[FD_READ_END]);
// 	if (execve(pipex->cmd, pipex->cmd_arguments, envp) == -1)
// 	{
// 		error("EXECVE2", pipex);
// 		// close (pipex->outfile);
// 	}
// }

void	child2(t_pipex *pipex, char *argv[], char *envp[])
{
	// if ((pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			// 0644)) < 0)
	// 	error("OUTFILE", pipex);

	if (!(pipex->cmd_arguments = ft_split(argv[3], ' ')))
		error("CMD2_ARGUMENT", pipex);
	// printf("cmd arguments %s\n", pipex->cmd_arguments[0]);
	// printf("cmd arguments %s\n", pipex->cmd_arguments[1]);
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_arguments[0]);
	if (!pipex->cmd)
		error("COMMAND2", pipex);
	dup2(pipex->end[FD_READ_END], STDIN_FILENO);
	//add by lin
	dup2(pipex->outfile, STDOUT_FILENO);
	//add by lin
	close(pipex->outfile);
	close(pipex->end[FD_READ_END]);
	close(pipex->end[FD_WRITE_END]);
	close(pipex->infile);
	// if outfile cannot be created, let's return after we close all the fds.
	if (pipex->outfile < 0)
		return;
	envp = NULL;

	if (execve(pipex->cmd, pipex->cmd_arguments, envp) == -1)
		error("EXECVE", pipex);
}
