/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:03:57 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/29 21:46:44 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	move_left_right(bool is_right, t_doom *params)
{
	double	old_dir_x;
	double	new_dir_x;
	double	new_dir_y;
	double	new_x;
	double	new_y;

	old_dir_x = params->pos_info.dir_x;
	new_dir_x = params->pos_info.dir_x
			* cos(is_right ? SPEED_RIGHT : SPEED_LEFT)
			- params->pos_info.dir_y * sin(is_right ? SPEED_RIGHT : SPEED_LEFT);
	new_dir_y = old_dir_x
			* sin(is_right ? SPEED_RIGHT : SPEED_LEFT)
			+ params->pos_info.dir_y * cos(is_right ? SPEED_RIGHT : SPEED_LEFT);
	new_y = params->pos_info.pos_y + new_dir_y
			* params->pos_info.move_speed / 2;
	new_x = params->pos_info.pos_x + new_dir_x
			* params->pos_info.move_speed / 2;
	if (params->map[(int)new_y][(int)params->pos_info.pos_x] < 1
		|| params->map[(int)new_y][(int)params->pos_info.pos_x] > 9)
		params->pos_info.pos_y = new_y;
	if (params->map[(int)params->pos_info.pos_y][(int)new_x] < 1
		|| params->map[(int)params->pos_info.pos_y][(int)new_x] > 9)
		params->pos_info.pos_x = new_x;
}

static void	move_forward_back(bool is_move_forward, t_doom *params)
{
	double	new_y;
	double	new_x;

	new_y = is_move_forward
			? params->pos_info.pos_y
				+ params->pos_info.dir_y * params->pos_info.move_speed
			: params->pos_info.pos_y
				- params->pos_info.dir_y * params->pos_info.move_speed;
	new_x = is_move_forward
			? params->pos_info.pos_x
				+ params->pos_info.dir_x * params->pos_info.move_speed
			: params->pos_info.pos_x
				- params->pos_info.dir_x * params->pos_info.move_speed;
	if (params->map[(int)new_y][(int)params->pos_info.pos_x] < 1
		|| params->map[(int)new_y][(int)params->pos_info.pos_x] > 9)
		params->pos_info.pos_y = new_y;
	if (params->map[(int)params->pos_info.pos_y][(int)new_x] < 1
		|| params->map[(int)params->pos_info.pos_y][(int)new_x] > 9)
		params->pos_info.pos_x = new_x;
}

void		route_events(t_doom *params)
{
	if (params->move_ev.ws == 1)
		move_forward_back(TRUE, params);
	else if (params->move_ev.ws == -1)
		move_forward_back(FALSE, params);
	else if (params->move_ev.ad == 1)
		move_left_right(FALSE, params);
	else if (params->move_ev.ad == -1)
		move_left_right(TRUE, params);
	sprites_pickup(params);
}
