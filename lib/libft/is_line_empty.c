/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:08:43 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/05 12:08:45 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_line_empty(char *line)
{
	while (*line)
	{
		if (*line != '\n' && *line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}
