/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:27 by abodnar           #+#    #+#             */
/*   Updated: 2019/05/01 17:45:28 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	load_hud_textures(t_doom *params)
{
	params->hud.main_hud = IMG_Load("./media/pics/hud.jpg");
	params->hud.face = IMG_Load("./media/pics/Aladdin.png");
	printf("%p\n", params->hud.face);
	params->hud.logo = IMG_Load("./media/pics/aladdin_small.png");
	params->menu.menu_tex = IMG_Load("./media/textures/menu.jpg");
	params->menu.lose_tex = IMG_Load("./media/textures/lose.jpg");
}

static void	load_sounds(t_doom *params)
{
	params->media.music = Mix_LoadMUS("./media/sounds/Prince_Outfit.mp3");
	params->media.sound1 = Mix_LoadWAV("./media/sounds/sound.mp3");
	params->media.sound2 = Mix_LoadWAV("./media/sounds/tiger.mp3");
}

static void	load_media(t_doom *params)
{
	load_wall_textures(params);
	load_sounds(params);
	load_hud_textures(params);
}

static void	init_helper(t_doom *params)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	params->sdl.surface = SDL_GetWindowSurface(params->sdl.window);
	load_media(params);
}

bool		init_sdl(t_doom *params)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		params->error = ft_strdup(SDL_GetError());
		return (FALSE);
	}
	if (!(params->sdl.window = SDL_CreateWindow("Doom-Aladdin",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
	{
		params->error = ft_strdup(SDL_GetError());
		return (FALSE);
	}
	if (TTF_Init() < 0)
	{
		params->error = ft_strdup(SDL_GetError());
		return (FALSE);
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		params->error = ft_strdup(SDL_GetError());
		return (FALSE);
	}
	init_helper(params);
	return (TRUE);
}
