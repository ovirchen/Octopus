/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:34:04 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 21:34:05 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		key_down(int key, t_doom *params)
{
	if (key == SDLK_UP || key == SDLK_w)
		params->move_ev.ws = 1;
	else if (key == SDLK_DOWN || key == SDLK_s)
		params->move_ev.ws = -1;
	if (key == SDLK_RIGHT || key == SDLK_d)
		params->move_ev.ad = -1;
	else if (key == SDLK_LEFT || key == SDLK_a)
		params->move_ev.ad = 1;
	else if (key == SDLK_SPACE)
		jump(params);
	else if (key == SDLK_p)
		squat(params);
	else if (key == SDLK_LCTRL)
		fly(params);
}
