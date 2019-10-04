/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:50:46 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 21:50:47 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	clear_map(t_doom *prm)
{
	int i;

	i = -1;
	while (++i < prm->map_height)
		ft_strdel((char**)&prm->map[i]);
	ft_strdel((char**)&prm->map);
}

void	clear_first(t_doom *prm)
{
	int	i;

	i = -1;
	while (++i < SPR_COUNT)
		SDL_FreeSurface(prm->media.sprites_textures[i]);
	i = -1;
	while (++i < TX_COUNT)
		SDL_FreeSurface(prm->media.textures[i]);
	SDL_FreeSurface(prm->media.floor_tex);
	SDL_FreeSurface(prm->media.ceil_tex);
}

void	clear_all(t_doom *prm)
{
	clear_first(prm);
	clear_map(prm);
	Mix_FreeMusic(prm->media.music);
	Mix_FreeChunk(prm->media.sound1);
	Mix_FreeChunk(prm->media.sound2);
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_FreeSurface(prm->sdl.surface);
	SDL_DestroyWindow(prm->sdl.window);
	SDL_Quit();
}
