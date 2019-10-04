/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:10:32 by abodnar           #+#    #+#             */
/*   Updated: 2019/05/05 14:10:32 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_sprite	*make_sprite(int y, int x, int id, t_doom *params)
{
	t_sprite	*result;

	result = (t_sprite*)ft_memalloc(sizeof(t_sprite));
	result->id = id;
	result->x = x;
	result->y = y;
	result->is_shown = id % 10 == 8 ? false : true;
	result->texture = params->media.sprites_textures[id % 10];
	return (result);
}

static void		parse_sprites(t_doom *params)
{
	int		i;
	int		j;
	int		k;

	params->sprites = (t_sprite**)ft_memalloc(sizeof(t_sprite)
			* (params->sprite_amount + 1));
	i = 0;
	k = 0;
	while (params->map[i] != NULL)
	{
		j = 0;
		while (params->map[i][j] != -1)
		{
			if (params->map[i][j] > 9 && params->map[i][j] < 20)
			{
				params->sprites[k] = make_sprite(i, j, params->map[i][j],
																	params);
				k++;
			}
			j++;
		}
		i++;
	}
	params->sprites[k] = NULL;
}

static int		*line_to_int_arr(char *line, t_doom *params)
{
	char	**splt;
	int		i;
	int		j;
	int		*res;

	splt = ft_strsplit(line, ' ');
	i = 0;
	while (splt[i])
		i++;
	res = (int*)ft_memalloc(sizeof(int) * (i + 1));
	j = -1;
	while (++j < i)
	{
		res[j] = ft_atoi(splt[j]);
		if (res[j] > 9 && res[j] < 20)
			params->sprite_amount++;
	}
	res[j] = -1;
	i = 0;
	while (splt[i])
		free(splt[i++]);
	free(splt);
	return (res);
}

void			parse_map(t_doom *params, char *raw_map)
{
	int		i;
	char	*map_cpy;
	char	*line;

	params->map = (int**)ft_memalloc(sizeof(int*) * (params->map_height + 1));
	map_cpy = raw_map;
	i = 0;
	while (i < params->map_height)
	{
		line = ft_strsub_chr(map_cpy, '\n');
		params->map[i] = line_to_int_arr(line, params);
		ft_strdel(&line);
		map_cpy = ft_strchr(map_cpy, '\n') + 1;
		i++;
	}
	params->map[i] = NULL;
	load_sprites_textures(params);
	parse_sprites(params);
	params->did_read_map = TRUE;
}
