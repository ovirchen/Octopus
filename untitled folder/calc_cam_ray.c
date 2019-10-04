/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_cam_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:23:08 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 21:23:09 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	calc_cam_ray(int x, t_doom *params, t_iterations *iter)
{
	iter->camera_x = (double)2.0 * (double)x / (double)(SCREEN_WIDTH)
				- (double)1.0;
	iter->ray_dir_x = params->pos_info.dir_x
				+ params->pos_info.plane_x * iter->camera_x;
	iter->ray_dir_y = params->pos_info.dir_y
				+ params->pos_info.plane_y * iter->camera_x;
	iter->map_x = (int)params->pos_info.pos_x;
	iter->map_y = (int)params->pos_info.pos_y;
	iter->delta_dist_x = fabs((double)1.0 / iter->ray_dir_x);
	iter->delta_dist_y = fabs((double)1.0 / iter->ray_dir_y);
}
