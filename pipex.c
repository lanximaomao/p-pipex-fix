/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:35:59 by atoof             #+#    #+#             */
/*   Updated: 2023/03/05 13:39:13 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//problem:

// ./pipex mm.c  "cat" "head -1" outfile
// ./pipex "/dev/urandom" "cat" "head -1" outfile


#include "pipex.h"
#include <stdio.h>

extern char	**environ;

/*find_path ignores "PATH=" and returns the rest*/
/*The waitpid() function is used in the parent process
to wait for the termination of its child processes.
In this case, there are two child processes with PIDs
pipex.pid1 and pipex.pid2. The waitpid() function blocks
the execution of the parent process until these child
processes have completed. This is necessary to ensure
that the child processes are able to finish their execution
and release any resources they may have acquired,
before the parent process continues with its execution and potentially exits.*/

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->end[0]);
	close(pipex->end[1]);
}

// int	main(int argc, char **argv)
// {
// 	t_pipex	*pipex;

// 	// ft_bzero(&pipex, sizeof(t_pipex));
// 	if (argc != 5)
// 		error("ARGUMENTS", NULL);

// 	pipex = malloc(sizeof(t_pipex));//malloc protection
// 	if (!pipex)
// 		error("MALLOC", NULL);
// 	if ((pipex->infile = open(argv[1], O_RDONLY)) < 0)
// 		error("INFILE", pipex);
// 	if ((pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
					// 0644)) < 0)
// 		error("OUTFILE", pipex);
// 	if (pipe(pipex->end) < 0)
// 		error("PIPE", pipex);
// 	pipex->cmd_paths = ft_split(find_path(environ), ':');
// 	// printf("my path folder %s\n", pipex.cmd_paths[0]);
// 	// printf("my path folder %s\n", pipex.cmd_paths[1]);
// 	// pipex.paths = pipex.cmd_paths; // set paths to cmd_paths initially
// 	if (!pipex->cmd_paths)
// 		error("PATH", pipex);
// 	pipex->pid1 = fork();
// 	if (pipex->pid1 < 0)
// 		error("FORK", pipex);
// 	else if (pipex->pid1 == 0)
// 		child1(pipex, argv, environ);
// 	pipex->pid2 = fork();
// 	if (pipex->pid2 < 0)
// 		error("FORK", pipex);
// 	else if (pipex->pid2 == 0)
// 		child2(pipex, argv, environ);
// 	waitpid(pipex->pid1, NULL, 0);
// 	waitpid(pipex->pid2, NULL, 0);
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	close(pipex->end[FD_WRITE_END]);
// 	close(pipex->end[FD_READ_END]);
// 	// free_pipex(pipex);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_pipex	*pipex;

	if (argc != 5)
		error("ARGUMENTS", NULL);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error("MALLOC", NULL);
	if ((pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
				0644)) < 0)
		perror("OUTFILE");//exit is now at child2 process
	if ((pipex->infile = open(argv[1], O_RDONLY)) < 0)
	//add by lin. don't exit, otherwise outfile won't be created.
		perror("infile");
		//error("INFILE", pipex);
	if (pipe(pipex->end) < 0)
		error("PIPE", pipex);
	pipex->cmd_paths = ft_split(find_path(environ), ':');
	if (!pipex->cmd_paths)
		error("PATH", pipex);

	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error("FORK", pipex);
	else if (pipex->pid1 == 0)
		child1(pipex, argv, environ);


	//comment out by Lin
	//close(pipex->end[FD_WRITE_END]);
	//pipex->infile = pipex->end[FD_READ_END];
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error("FORK", pipex);
	else if (pipex->pid2 == 0)
		child2(pipex, argv, environ);

	//waitpid(pipex->pid1, NULL, 0);
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->end[FD_WRITE_END]);
	close(pipex->end[FD_READ_END]);
	//lin: close before you wait!!
	waitpid(pipex->pid2, NULL, 0);
	return (0);
}
