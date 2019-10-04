/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:13 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/29 21:02:39 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_parameters(t_doom *params)
{
	ft_bzero(params, sizeof(t_doom));
	params->is_working = 1;
	params->map_height = 1;
	params->wall_x = 0.0;
	params->ray_x = 0;
	params->ray_y = 0;
	params->squat = FALSE;
	params->fly = FALSE;
}
