/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:20:59 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 21:21:00 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	load_wall_textures(t_doom *params)
{
	params->media.textures[0] = IMG_Load("./media/textures/fire_smart5.jpg");
	params->media.textures[1] = IMG_Load("./media/textures/fire_smart1.jpg");
	params->media.textures[2] = IMG_Load("./media/textures/green_smart1.jpg");
	params->media.textures[3] = IMG_Load("./media/textures/fire_smart3.jpg");
	params->media.textures[4] = IMG_Load("./media/textures/fire_smart4.jpg");
	params->media.textures[5] = IMG_Load("./media/textures/water.jpg");
	params->media.textures[6] = IMG_Load("./media/textures/sky_smart1.jpg");
	params->media.textures[7] = IMG_Load("./media/textures/sky_smart2.jpg");
	params->media.textures[8] = IMG_Load("./media/textures/sky_smart3.jpg");
	params->media.floor_tex = IMG_Load("./media/textures/sky_smart4.jpg");
	params->media.ceil_tex = IMG_Load("./media/textures/fire_smart.jpg");
}
