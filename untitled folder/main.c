/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:41 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 12:12:50 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	process_jump(t_doom *params)
{
	int i;

	Mix_PlayChannel(-1, params->media.sound1, 0);
	i = -1;
	while (++i < JUMP_HEIGHT)
	{
		params->pos_info.jump -= 1;
		make_calculations(params);
		draw_hud(params);
		SDL_UpdateWindowSurface(params->sdl.window);
	}
}

static void	process_game(t_doom *params)
{
	check_event(params);
	if (params->move_ev.mws || params->move_ev.ad || params->move_ev.ws
		|| params->move_ev.mad)
	{
		route_events(params);
		route_mouse_move(params);
		make_calculations(params);
		draw_sprites(params);
		draw_hud(params);
		SDL_UpdateWindowSurface(params->sdl.window);
	}
	else if (params->pos_info.jump > 0)
		process_jump(params);
}

int			main(int ac, char **av)
{
	t_doom	params;

	ft_bzero(&params, sizeof(t_doom));
	if (!check_arguments(ac, &params))
		return (handle_error(&params));
	init_parameters(&params);
	if (!read_map(&params, av[1]))
		return (handle_map_error(&params));
	if (!init_sdl(&params))
		return (handle_error(&params));
	init_position(&params);
	make_calculations(&params);
	draw_hud(&params);
	Mix_PlayMusic(params.media.music, 1);
	while (params.is_working && !params.win && !params.died)
		process_game(&params);
	process_finish(&params);
	clear_all(&params);
	return (0);
}
