/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:27 by atoof             #+#    #+#             */
/*   Updated: 2023/03/03 16:26:48 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error, t_pipex *pipex)
{
	free_pipex(pipex);
	perror(error);
	exit(EXIT_FAILURE);
}
