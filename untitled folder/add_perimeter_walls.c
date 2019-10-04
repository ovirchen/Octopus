/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_perimeter_walls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:09:36 by abodnar           #+#    #+#             */
/*   Updated: 2019/05/05 14:09:37 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	check_border(int y, int x, int **map)
{
	int	i;

	i = 0;
	while (y != 0 && map[y - 1][i] != -1)
		i++;
	if (i <= x)
		return (TRUE);
	i = 0;
	while (map[y + 1] && map[y + 1][i] != -1)
		i++;
	if (i <= x)
		return (TRUE);
	return (FALSE);
}

void		add_perimeter_walls(int **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != -1)
			if (i == 0
			|| map[i + 1] == NULL
			|| j == 0
			|| map[i][j + 1] == -1
			|| check_border(i, j, map))
				map[i][j] = 1;
	}
}
