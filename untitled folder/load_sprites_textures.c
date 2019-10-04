/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:35:14 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 15:35:15 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		load_sprites_textures(t_doom *params)
{
	params->media.sprites_textures[0] = IMG_Load("./media/pics/abu.png");
	params->media.sprites_textures[1] = IMG_Load("./media/pics/carpet.png");
	params->media.sprites_textures[2] = IMG_Load("./media/pics/coins.png");
	params->media.sprites_textures[3] = IMG_Load("./media/pics/djinn.png");
	params->media.sprites_textures[4] = IMG_Load("./media/pics/flamingo.png");
	params->media.sprites_textures[5] = IMG_Load("./media/pics/lamp.png");
	params->media.sprites_textures[6] = IMG_Load("./media/pics/parrot.png");
	params->media.sprites_textures[7] = IMG_Load("./media/pics/yago.gif");
	params->media.sprites_textures[8] = IMG_Load("./media/pics/jasmin.png");
	params->media.sprites_textures[9] = IMG_Load("./media/pics/tiger.png");
}
