/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:08:02 by pshchuro          #+#    #+#             */
/*   Updated: 2019/06/30 12:12:09 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		check_floor_dir(t_doom *params, t_draw_floor *dr)
{
	if (params->side == 0 && params->sdl.ray_dir_x > 0)
	{
		dr->floor_x = params->sdl.map_x;
		dr->floor_y = params->sdl.map_y + params->wall_x;
	}
	else if (params->side == 0 && params->sdl.ray_dir_x < 0)
	{
		dr->floor_x = params->sdl.map_x + 1.0;
		dr->floor_y = params->sdl.map_y + params->wall_x;
	}
	else if (params->side == 1 && params->sdl.ray_dir_y > 0)
	{
		dr->floor_x = params->sdl.map_x + params->wall_x;
		dr->floor_y = params->sdl.map_y;
	}
	else
	{
		dr->floor_x = params->sdl.map_x + params->wall_x;
		dr->floor_y = params->sdl.map_y + 1.0;
	}
}

static void		ceilinig_draw(int x, t_doom *p, t_draw_floor *dr)
{
	while (dr->wall_start >= 0)
	{
		dr->cur_dist = SCREEN_HEIGHT / (2.0 * -dr->wall_start + \
						SCREEN_HEIGHT + 2 * p->pos_info.h);
		dr->weight = (dr->cur_dist - dr->dist_pl) / (dr->dist_wall
				- dr->dist_pl);
		dr->cur_floor_x = dr->weight * dr->floor_x + (1.0 - dr->weight)
				* p->pos_info.pos_x;
		dr->cur_floor_y = dr->weight * dr->floor_y + (1.0 - dr->weight)
				* p->pos_info.pos_y;
		dr->floor_tex_x = (int)(dr->cur_floor_x * p->media.floor_tex->w)
				% p->media.floor_tex->w;
		dr->floor_tex_y = (int)(dr->cur_floor_y * p->media.floor_tex->h)
				% p->media.floor_tex->h;
		dr->ceil_pos = x + (dr->wall_start * SCREEN_WIDTH);
		dr->pixels[dr->ceil_pos] = set_color(((int*)p->media.floor_tex->pixels)
			[p->media.floor_tex->w * dr->floor_tex_y + dr->floor_tex_x],
				dr->cur_dist);
		dr->wall_start--;
	}
}

void			draw_textured_ceiling(int x, int height, t_doom *p)
{
	t_draw_floor	dr;

	ft_bzero(&dr, sizeof(t_draw_floor));
	dr.wall_start = calculate_start(height, p);
	dr.wall_end = calculate_end(height, p);
	dr.pixels = p->sdl.surface->pixels;
	check_floor_dir(p, &dr);
	dr.dist_wall = p->pos_info.perp_wall_dist;
	dr.dist_pl = 0.0;
	ceilinig_draw(x, p, &dr);
}

static void		floor_draw(int x, t_doom *p, t_draw_floor *dr)
{
	while (dr->wall_end < SCREEN_HEIGHT)
	{
		dr->pos = x + (dr->wall_end * SCREEN_WIDTH);
		dr->cur_dist = SCREEN_HEIGHT / (2.0 * dr->wall_end
				- SCREEN_HEIGHT - 2 * p->pos_info.h);
		dr->weight = (dr->cur_dist - dr->dist_pl)
				/ (dr->dist_wall - dr->dist_pl);
		dr->cur_floor_x = dr->weight * dr->floor_x + (1.0 - dr->weight)
				* p->pos_info.pos_x;
		dr->cur_floor_y = dr->weight * dr->floor_y + (1.0 - dr->weight)
				* p->pos_info.pos_y;
		dr->floor_tex_x = (int)(dr->cur_floor_x * p->media.ceil_tex->w)
				% p->media.ceil_tex->w;
		dr->floor_tex_y = (int)(dr->cur_floor_y * p->media.ceil_tex->h)
				% p->media.ceil_tex->h;
		dr->pixels[dr->pos] = set_color(((int*)p->media.ceil_tex->pixels)
			[p->media.ceil_tex->w * dr->floor_tex_y + dr->floor_tex_x],
				dr->cur_dist);
		dr->wall_end++;
	}
}

void			draw_textured_floor(int x, int height, t_doom *p)
{
	t_draw_floor	dr;

	ft_bzero(&dr, sizeof(t_draw_floor));
	dr.wall_start = calculate_start(height, p);
	dr.wall_end = calculate_end(height, p);
	dr.pixels = p->sdl.surface->pixels;
	check_floor_dir(p, &dr);
	dr.dist_wall = p->pos_info.perp_wall_dist;
	dr.dist_pl = 0.0;
	floor_draw(x, p, &dr);
}
