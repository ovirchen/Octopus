/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:13:58 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/29 20:13:59 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				amount_clear(t_doom *params)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (i < params->sprite_amount)
	{
		if (params->sprites[i]->id < 18)
			res++;
		i++;
	}
	return (res);
}

static void		prepare_hud_text(t_doom *params)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup("Collected: ");
	temp2 = ft_itoa(params->sprite_picked);
	temp1 = ft_str_clean_join(&temp1, &temp2);
	temp2 = ft_strdup("/");
	temp1 = ft_str_clean_join(&temp1, &temp2);
	temp2 = ft_itoa(amount_clear(params));
	temp1 = ft_str_clean_join(&temp1, &temp2);
	params->hud.text = temp1;
}

static void		draw_sprites_text(t_doom *params)
{
	SDL_Surface	*text_surface;
	SDL_Rect	sprites_rect;
	TTF_Font	*font;
	SDL_Color	color;

	sprites_rect = (SDL_Rect){900, SCREEN_HEIGHT - 72, 100, 60};
	color = (SDL_Color){0, 0, 0, 255};
	font = TTF_OpenFont("./media/fonts/aladdin.ttf", 39);
	if (font == NULL)
		params->error = ft_strdup(SDL_GetError());
	prepare_hud_text(params);
	if (!(text_surface = TTF_RenderText_Solid(font, params->hud.text, color)))
		ft_printf("error\n");
	else
		SDL_BlitSurface(text_surface, NULL, params->sdl.surface, &sprites_rect);
	TTF_CloseFont(font);
	ft_strdel(&params->hud.text);
	SDL_FreeSurface(text_surface);
}

static void		draw_jasmine_text(t_doom *params)
{
	SDL_Surface	*text_surface;
	SDL_Rect	jasmin_rect;
	TTF_Font	*font;
	SDL_Color	color;

	jasmin_rect = (SDL_Rect){500, SCREEN_HEIGHT - 72, 200, 120};
	color = (SDL_Color){255, 255, 255, 255};
	font = TTF_OpenFont("./media/fonts/aladdin.ttf", 39);
	if (font == NULL)
		params->error = ft_strdup(SDL_GetError());
	if (!(text_surface = TTF_RenderText_Solid(font, "Find Jasmine!", color)))
		ft_printf("error\n");
	else
		SDL_BlitSurface(text_surface, NULL, params->sdl.surface, &jasmin_rect);
	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
}

void			draw_hud(t_doom *params)
{
	SDL_Rect	main_rect;
	SDL_Rect	face_rect;
	SDL_Rect	logo_rect;

	main_rect = (SDL_Rect){0, 700, SCREEN_WIDTH, 100};
	SDL_BlitSurface(params->hud.main_hud, NULL, params->sdl.surface,
																&main_rect);
	face_rect = (SDL_Rect){100, SCREEN_HEIGHT - 100, 100, 100};
	SDL_BlitSurface(params->hud.face, NULL, params->sdl.surface, &face_rect);
	logo_rect = (SDL_Rect){face_rect.x + face_rect.w + 10, face_rect.y
																+ 25, 129, 50};
	SDL_BlitSurface(params->hud.logo, NULL, params->sdl.surface, &logo_rect);
	draw_jasmine_text(params);
	draw_sprites_text(params);
}
