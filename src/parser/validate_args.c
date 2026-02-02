/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:04:59 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/02 12:05:01 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	exit_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	validate_args(int argc, char **argv)
{
	int	len;
	int	fd;

	if (argc != 2)
		exit_error(ERR_USAGE);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
		exit_error(ERR_INVALID_EXTENSION);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			exit_error(ERR_FILE_NOT_FOUND);
		else if (errno == EACCES)
			exit_error(ERR_PERMISSION_DENIED);
		else
			exit_error(ERR_CANNOT_OPEN_FILE);
	}
	close(fd);
}