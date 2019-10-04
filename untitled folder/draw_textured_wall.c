/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:53:19 by pshchuro          #+#    #+#             */
/*   Updated: 2019/06/30 12:07:22 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		set_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r << 16) | (g << 8) | b);
}

Uint32	set_color(int color, double dist)
{
	Uint32 color_new;

	if (dist > 1)
		color_new = (Uint32)set_rgb((unsigned int)(((color & 0x00ff0000) >> 16)\
					/ dist), (unsigned int)(((color & 0x0000ff00) >> 8) / dist),
					(unsigned int)(((color & 0x000000ff)) / dist));
	else
		color_new = (Uint32)color;
	return (color_new);
}

int		calculate_start(int height, t_doom *params)
{
	int start;

	start = (SCREEN_HEIGHT - height) / 2 + params->pos_info.h;
	start = start < 0 ? 0 : start;
	start = start >= SCREEN_HEIGHT ? SCREEN_HEIGHT - 1 : start;
	return (start);
}

int		calculate_end(int height, t_doom *params)
{
	int end;

	end = (SCREEN_HEIGHT + height) / 2 + params->pos_info.h;
	end = end < 0 ? 0 : end;
	end = end >= SCREEN_HEIGHT ? SCREEN_HEIGHT - 1 : end;
	return (end);
}

void	draw_textured_wall(int x, int height, t_doom *p)
{
	t_draw_wall	dr;

	ft_bzero(&dr, sizeof(t_draw_wall));
	dr.wall_start = calculate_start(height, p);
	dr.wall_end = calculate_end(height, p);
	dr.pixels = (Uint32*)p->sdl.surface->pixels;
	p->wall_color = 0;
	while (dr.wall_start < dr.wall_end)
	{
		dr.pos = x + (dr.wall_start * SCREEN_WIDTH);
		dr.tex_x = (int)(p->wall_x * (double)p->media.textures[p->tex_ind]->w);
		if ((p->side == 0 && p->ray_x > 0) || (p->side == 1 && p->ray_y < 0))
			dr.tex_x = p->media.textures[p->tex_ind]->w - dr.tex_x - 1;
		dr.d = dr.wall_start * 2 - SCREEN_HEIGHT + height - \
				p->pos_info.h * 2;
		dr.tex_y = ((dr.d * p->media.textures[p->tex_ind]->w) / height) / 2;
		if (dr.tex_x >= 0 && dr.tex_x < p->media.textures[p->tex_ind]->h &&\
			dr.tex_y >= 0 && dr.tex_y < p->media.textures[p->tex_ind]->w)
			p->wall_color = set_color(((int*)p->media.textures\
			[p->tex_ind]->pixels)[p->media.textures[p->tex_ind]->h\
			* dr.tex_y + dr.tex_x], p->z_buffer[x]);
		dr.pixels[dr.pos] = p->wall_color;
		dr.wall_start++;
	}
}
