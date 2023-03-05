/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:39:21 by atoof             #+#    #+#             */
/*   Updated: 2023/03/03 20:45:41 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_file_descriptors(t_pipex *pipex)
{
	if (pipex)
	{
		close(pipex->infile);
		close(pipex->outfile);
	}
}

void	free_double_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->cmd)
			free(pipex->cmd);
		if (pipex->cmd_paths)
			free_double_array(pipex->cmd_paths);
		if (pipex->cmd_arguments)
			free_double_array(pipex->cmd_arguments);
		if (pipex->paths)
			free_double_array(pipex->paths);
	}
}
