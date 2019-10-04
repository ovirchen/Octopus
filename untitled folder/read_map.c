/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:25 by abodnar           #+#    #+#             */
/*   Updated: 2019/05/01 17:46:26 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	find_empty_position(t_doom *params, int **map)
{
	int	i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != -1)
		{
			if (map[i][j] == 0)
			{
				params->pos_info.pos_y = i;
				params->pos_info.pos_x = j;
				return (TRUE);
			}
			j++;
		}
		i++;
	}
	params->error = ft_strdup("No position for player on map!");
	return (FALSE);
}

static bool	check_map(t_doom *params, char *raw_map)
{
	char	*symbols;
	char	*map_cpy;

	symbols = ft_strdup("1234567890 \n");
	map_cpy = raw_map;
	while (*map_cpy)
	{
		if (ft_strchr(symbols, *map_cpy) == NULL)
		{
			params->error = ft_strdup("Incorrect symbols in map!\n");
			ft_strdel(&symbols);
			return (FALSE);
		}
		map_cpy++;
	}
	ft_strdel(&symbols);
	return (TRUE);
}

static char	*read_file(t_doom *params, char *input, int fd)
{
	char	*res;
	char	*cpy;
	char	buf[READ_SIZE + 1];

	if ((fd = open(input, O_RDONLY)) == -1)
		return (NULL);
	res = ft_strnew(0);
	ft_bzero(buf, READ_SIZE);
	while (read(fd, buf, READ_SIZE) > 0)
	{
		buf[READ_SIZE] = '\0';
		cpy = res;
		res = ft_strjoin(res, buf);
		ft_strdel(&cpy);
		ft_bzero(buf, READ_SIZE);
	}
	close(fd);
	cpy = res;
	while (*cpy)
	{
		if (*cpy == '\n' && *(cpy + 1) != '\n' && *(cpy + 1) != '\0')
			params->map_height++;
		cpy++;
	}
	return (res);
}

bool		read_map(t_doom *params, char *input)
{
	char	*raw_map;
	char	*cpy;

	if ((raw_map = read_file(params, input, 0)) == NULL)
	{
		params->error = ft_strdup("Read map error");
		return (FALSE);
	}
	cpy = raw_map;
	raw_map = ft_strtrim(raw_map);
	ft_strdel(&cpy);
	if (check_map(params, raw_map) == FALSE)
		return (FALSE);
	parse_map(params, raw_map);
	ft_strdel(&raw_map);
	add_perimeter_walls(params->map);
	if (find_empty_position(params, params->map) == FALSE)
		return (FALSE);
	return (TRUE);
}
