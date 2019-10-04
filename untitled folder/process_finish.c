/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:33:42 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 20:33:43 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	process_win(t_doom *params)
{
	SDL_Surface	*text_surface;
	SDL_Rect	sprites_rect;
	SDL_Color	color;
	SDL_Rect	menu_rect;

	menu_rect = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitSurface(params->menu.menu_tex, NULL, params->sdl.surface,
			&menu_rect);
	SDL_UpdateWindowSurface(params->sdl.window);
	sprites_rect = (SDL_Rect){450, SCREEN_HEIGHT - 500, 100, 60};
	color = (SDL_Color){255, 255, 255, 255};
	params->media.font = TTF_OpenFont("./media/fonts/excalibur.ttf", 39);
	text_surface = TTF_RenderText_Solid(params->media.font, "You won the game!",
			color);
	SDL_BlitSurface(text_surface, NULL, params->sdl.surface, &sprites_rect);
	SDL_UpdateWindowSurface(params->sdl.window);
	TTF_CloseFont(params->media.font);
	SDL_FreeSurface(text_surface);
	sleep(3);
}

static void	process_died(t_doom *params)
{
	SDL_Surface	*text_surface;
	SDL_Rect	sprites_rect;
	SDL_Color	color;
	SDL_Rect	menu_rect;

	menu_rect = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitSurface(params->menu.lose_tex, NULL, params->sdl.surface,
			&menu_rect);
	SDL_UpdateWindowSurface(params->sdl.window);
	sprites_rect = (SDL_Rect){445, SCREEN_HEIGHT - 750, 100, 60};
	color = (SDL_Color){255, 255, 255, 255};
	params->media.font = TTF_OpenFont("./media/fonts/excalibur.ttf", 39);
	text_surface = TTF_RenderText_Solid(params->media.font,
			"You lost the game!", color);
	SDL_BlitSurface(text_surface, NULL, params->sdl.surface, &sprites_rect);
	SDL_UpdateWindowSurface(params->sdl.window);
	TTF_CloseFont(params->media.font);
	SDL_FreeSurface(text_surface);
	sleep(3);
}

void		process_finish(t_doom *params)
{
	if (params->died)
		process_died(params);
	else if (params->win)
		process_win(params);
}
