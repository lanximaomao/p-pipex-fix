/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 04:10:46 by atoof             #+#    #+#             */
/*   Updated: 2023/03/03 13:14:18 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **environ)
{
	t_pipex	pipex;

	if (argc != 5)
		error("usage: ./pipex file1 cmd1 cmd2 file2", &pipex);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		error("input file does not exist", &pipex);
	pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.outfile == -1)
		error("cannot create output file", &pipex);
	pipex.cmd_paths = ft_split(getenv("PATH"), ':');
	if (!pipex.cmd_paths)
		error("cannot get PATH variable", &pipex);
	pipex.cmd_arguments = ft_split(argv[2], ' ');
	if (!pipex.cmd_arguments)
		error("cannot split command arguments", &pipex);
	pipex.fst_cmd = ft_strdup(argv[2]);
	if (!pipex.fst_cmd)
		error("cannot duplicate first command", &pipex);
	pipex.snd_cmd = ft_strdup(argv[3]);
	if (!pipex.snd_cmd)
		error("cannot duplicate second command", &pipex);
	parent_process(&pipex, argv, environ);
	parent_free(&pipex);
	return (0);
}
