/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:17:37 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 18:42:26 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	draw_sprites_prepare(t_dr_spr *d, t_doom *params)
{
	d->spr_x = params->sprites[d->ind]->x - params->pos_info.pos_x;
	d->spr_y = params->sprites[d->ind]->y - params->pos_info.pos_y;
	d->inv_det = 1.0 / (params->pos_info.plane_x * params->pos_info.dir_y
					- params->pos_info.dir_x * params->pos_info.plane_y);
	d->transf_x = d->inv_det * (params->pos_info.dir_y * d->spr_x
					- params->pos_info.dir_x * d->spr_y);
	d->transf_y = d->inv_det * (-params->pos_info.plane_y * d->spr_x
					+ params->pos_info.plane_x * d->spr_y);
	d->spr_scr_x = (int)((SCREEN_WIDTH / 2) * (1 + d->transf_x / d->transf_y));
	d->spr_h = abs((int)(SCREEN_HEIGHT / (d->transf_y)));
	d->draw_start_y = -d->spr_h / 2 + SCREEN_HEIGHT / 2 + params->pos_info.h;
	if (d->draw_start_y < 0)
		d->draw_start_y = 0;
	d->draw_end_y = d->spr_h / 2 + SCREEN_HEIGHT / 2 + params->pos_info.h;
	if (d->draw_end_y >= SCREEN_HEIGHT)
		d->draw_end_y = SCREEN_HEIGHT - 1;
	d->spr_w = abs((int)(SCREEN_HEIGHT / (d->transf_y)));
	d->draw_start_x = -d->spr_w / 2 + d->spr_scr_x;
	if (d->draw_start_x < 0)
		d->draw_start_x = 0;
	d->draw_end_x = d->spr_w / 2 + d->spr_scr_x;
	if (d->draw_end_x >= SCREEN_WIDTH)
		d->draw_end_x = SCREEN_WIDTH - 1;
	d->i = d->draw_start_x;
}

static void	draw_sprites_main(t_dr_spr *d, t_doom *params)
{
	while (d->i < d->draw_end_x)
	{
		d->tex_x = (int)(256 * (d->i - (-d->spr_w / 2 + d->spr_scr_x))
						* params->sprites[d->ind]->texture->w / d->spr_w) / 256;
		if (d->transf_y > 0 && d->i > 0 && d->i < SCREEN_WIDTH
			&& d->transf_y < params->z_buffer[d->i])
		{
			d->j = d->draw_start_y;
			while (d->j < d->draw_end_y)
			{
				d->pos = d->i + (d->j * SCREEN_WIDTH);
				d->d = d->j * 256 - SCREEN_HEIGHT * 128 + d->spr_h * 128 - 256
						* params->pos_info.h;
				d->tex_y = ((d->d * params->sprites[d->ind]->texture->h)
						/ d->spr_h) / 256;
				d->color = ((Uint32*)params->sprites[d->ind]->texture->pixels)
				[params->sprites[d->ind]->texture->w * d->tex_y + d->tex_x];
				if ((d->color & 0x00FFFFFF) != 0)
					((Uint32*)params->sdl.surface->pixels)[d->pos] = d->color;
				d->j++;
			}
		}
		d->i++;
	}
}

void		draw_sprites(t_doom *params)
{
	t_dr_spr	d;

	d.ind = 0;
	while (d.ind < params->sprite_amount)
	{
		if (params->sprites[d.ind]->is_shown)
		{
			draw_sprites_prepare(&d, params);
			draw_sprites_main(&d, params);
		}
		d.ind++;
	}
}
