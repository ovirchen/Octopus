/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly_jump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:14:24 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 21:14:24 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	recalc(t_doom *params)
{
	make_calculations(params);
	draw_sprites(params);
	draw_hud(params);
	SDL_UpdateWindowSurface(params->sdl.window);
}

void		jump(t_doom *params)
{
	int height;
	int delta_height;

	if (!params->fly && !params->squat)
	{
		height = params->pos_info.h;
		delta_height = 0;
		while (delta_height < 100)
		{
			params->pos_info.h = height + delta_height;
			recalc(params);
			delta_height += 10;
		}
		while (delta_height >= 0)
		{
			params->pos_info.h = height + delta_height;
			recalc(params);
			delta_height -= 10;
		}
	}
}

void		fly(t_doom *params)
{
	int delta;

	delta = 250;
	if (!params->fly && !params->squat)
	{
		params->fly = TRUE;
		while (delta > 0)
		{
			params->pos_info.h += 25;
			delta -= 25;
			recalc(params);
		}
	}
	else if (!params->squat)
	{
		params->fly = FALSE;
		while (delta > 0)
		{
			delta -= 25;
			params->pos_info.h -= 25;
			recalc(params);
		}
	}
}

void		squat(t_doom *params)
{
	int delta;

	delta = 250;
	if (!params->squat && !params->fly)
	{
		params->squat = TRUE;
		while (delta > 0)
		{
			params->pos_info.h -= 25;
			delta -= 25;
			recalc(params);
		}
	}
	else if (!params->fly)
	{
		params->squat = FALSE;
		while (delta > 0)
		{
			delta -= 25;
			params->pos_info.h += 25;
			recalc(params);
		}
	}
}
