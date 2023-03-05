/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:25:44 by atoof             #+#    #+#             */
/*   Updated: 2023/03/03 20:08:41 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
#include <sys/stat.h>

# define FD_WRITE_END 1
# define FD_READ_END 0

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int 	end[2];           // Need close
	int 	infile;           // Need close
	int 	outfile;          // Need close
	char 	**cmd_paths;     // Free
	char 	**cmd_arguments; // Free
	char 	*cmd;            // Free
	char    **paths;  // new field for paths array
}			t_pipex;

void		free_pipex(t_pipex *pipex);
void		error(char *error, t_pipex *pipex);
// void		parent_free(t_pipex *pipex);
void		child1(t_pipex *pipex, char **argv, char **envp);
void		child2(t_pipex *pipex, char **argv, char **envp);
// void		free_child(t_pipex *pipex);
void		close_file_descriptors(t_pipex *pipex);

#endif
