/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:43:29 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 20:29:06 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		key_up(int key, t_doom *params)
{
	if (key == SDLK_UP || key == SDLK_w)
		params->move_ev.ws = 0;
	else if (key == SDLK_DOWN || key == SDLK_s)
		params->move_ev.ws = 0;
	else if (key == SDLK_RIGHT || key == SDLK_d)
		params->move_ev.ad = 0;
	else if (key == SDLK_LEFT || key == SDLK_a)
		params->move_ev.ad = 0;
}

void		define_mouse(t_doom *params)
{
	if (params->move_ev.code.motion.xrel > 0)
		params->move_ev.mws = -1;
	else if (params->move_ev.code.motion.xrel < 0)
		params->move_ev.mws = 1;
	if (params->move_ev.code.motion.yrel > 0)
		params->move_ev.mad = 1;
	else if (params->move_ev.code.motion.yrel < 0)
		params->move_ev.mad = -1;
}

static void	check_helper(t_doom *p, int type)
{
	if (type == 1)
	{
		SDL_FlushEvent(TP);
		return (key_down(SYM, p));
	}
	else if (type == 2)
	{
		SDL_FlushEvent(TP);
		return (key_up(SYM, p));
	}
}

static void	check_helper_more(t_doom *p)
{
	p->move_ev.mad = 0;
	p->move_ev.mws = 0;
	SDL_FlushEvent(TP);
}

void		check_event(t_doom *p)
{
	if (SDL_WaitEvent(&p->move_ev.code))
	{
		if ((TP == SDL_QUIT) || (TP == SDL_KEYDOWN && SYM == SDLK_ESCAPE))
		{
			p->is_working = 0;
			SDL_FlushEvent(TP);
			return ;
		}
		else if (TP == SDL_KEYDOWN)
			return (check_helper(p, 1));
		else if (TP == SDL_KEYUP)
			return (check_helper(p, 2));
		else if (TP == SDL_MOUSEMOTION)
		{
			define_mouse(p);
			SDL_FlushEvent(TP);
			return ;
		}
		else if (p->move_ev.mouse.xrel == 0 && p->move_ev.mouse.yrel == 0)
		{
			check_helper_more(p);
			return ;
		}
		p->move_ev.mouse = p->move_ev.code.motion;
	}
}
