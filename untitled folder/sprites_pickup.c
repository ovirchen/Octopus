/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_pickup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:03:04 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 20:03:05 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	make_jasmin_visible(t_doom *params)
{
	int i;

	i = -1;
	while (++i < params->sprite_amount)
		if (params->sprites[i]->id == 18)
			params->sprites[i]->is_shown = true;
}

static int	position_has_sprite(t_doom *params)
{
	int i;

	i = -1;
	while (++i < params->sprite_amount)
	{
		if (params->sprites[i]->x == (int)params->pos_info.pos_x
			&& params->sprites[i]->y == (int)params->pos_info.pos_y
			&& params->sprites[i]->is_shown)
		{
			params->sprites[i]->is_shown = false;
			return (params->sprites[i]->id);
		}
	}
	return (0);
}

void		sprites_pickup(t_doom *params)
{
	int pos_sprite_id;

	pos_sprite_id = position_has_sprite(params);
	if (pos_sprite_id == 18)
		params->win = true;
	else if (pos_sprite_id == 19)
	{
		Mix_PlayChannel(-1, params->media.sound2, 0);
		params->died = true;
	}
	else if (pos_sprite_id > 0)
	{
		Mix_PlayChannel(-1, params->media.sound1, 0);
		params->sprite_picked++;
	}
	if (params->sprite_picked == amount_clear(params))
		make_jasmin_visible(params);
}
