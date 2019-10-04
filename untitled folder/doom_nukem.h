/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshchuro <pshchuro@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:15 by abodnar           #+#    #+#             */
/*   Updated: 2019/06/30 20:11:44 by pshchuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "libftprintf/libftprintf.h"
# include "frameworks/SDL2.framework/Headers/SDL.h"
# include "frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
# include "frameworks/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
# include "frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <math.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define TRUE 1
# define FALSE 0
# define READ_SIZE 32
# define DELTA_MOUSE 15

# define TX_COUNT 9
# define SPR_COUNT 10

# define SPEED_RIGHT -1.5
# define SPEED_LEFT 1.5

# define JUMP_HEIGHT 80

# define TP p->move_ev.code.type
# define SYM p->move_ev.code.key.keysym.sym

typedef struct	s_menu
{
	SDL_Surface	*menu_tex;
	SDL_Surface	*lose_tex;
	SDL_Color	color;
}				t_menu;

typedef	struct	s_move
{
	SDL_Event				code;
	int						ws;
	int						ad;
	int						mws;
	int						mad;
	SDL_MouseMotionEvent	mouse;
}				t_move;

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Event	event;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
}				t_sdl;

typedef struct	s_sprite
{
	SDL_Surface	*texture;
	int			x;
	int			y;
	bool		is_shown;
	int			id;
}				t_sprite;

typedef struct	s_hud
{
	SDL_Surface	*main_hud;
	SDL_Surface	*face;
	SDL_Surface	*logo;
	char		*text;
}				t_hud;

typedef struct	s_draw_wall
{
	int			wall_start;
	int			wall_end;
	Uint32		*pixels;
	int			tex_x;
	int			tex_y;
	int			d;
	int			pos;
}				t_draw_wall;

typedef struct	s_draw_floor
{
	int			wall_start;
	int			wall_end;
	Uint32		*pixels;
	double		floor_x;
	double		floor_y;
	int			pos;
	double		dist_wall;
	double		dist_pl;
	double		cur_dist;
	double		weight;
	double		cur_floor_x;
	double		cur_floor_y;
	int			floor_tex_x;
	int			floor_tex_y;
	int			ceil_pos;
}				t_draw_floor;

typedef struct	s_position
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotate_speed;
	int			h;
	double		jump;
	double		perp_wall_dist;
}				t_position;

typedef struct	s_media
{
	SDL_Surface	*sprites_textures[SPR_COUNT];
	SDL_Surface *textures[TX_COUNT];
	SDL_Surface	*ceil_tex;
	SDL_Surface	*floor_tex;
	Mix_Music	*music;
	Mix_Chunk	*sound1;
	Mix_Chunk	*sound2;
	TTF_Font	*font;
}				t_media;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_position	pos_info;
	int			**map;
	int			map_height;
	bool		is_working;
	bool		did_read_map;
	char		*error;
	int			side;
	Uint32		wall_color;
	int			tex_ind;
	t_hud		hud;
	double		wall_x;
	double		ray_x;
	double		ray_y;
	double		z_buffer[SCREEN_WIDTH];
	t_move		move_ev;
	bool		squat;
	bool		fly;
	int			sprite_amount;
	int			sprite_picked;
	t_sprite	**sprites;
	t_media		media;
	t_menu		menu;
	bool		win;
	bool		died;
}				t_doom;

typedef struct	s_iteration
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
}				t_iterations;

typedef struct	s_dr_spr
{
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	transf_x;
	double	transf_y;
	int		spr_scr_x;
	int		spr_h;
	int		draw_start_y;
	int		draw_end_y;
	int		spr_w;
	int		draw_start_x;
	int		draw_end_x;
	int		i;
	int		j;
	int		tex_x;
	int		tex_y;
	int		pos;
	int		d;
	Uint32	color;
	int		ind;
}				t_dr_spr;

bool			check_arguments(int ac, t_doom *params);
int				handle_error(t_doom *params);
void			init_parameters(t_doom *params);
bool			read_map(t_doom *params, char *input);
int				handle_map_error(t_doom *params);
bool			init_sdl(t_doom *params);
void			init_position(t_doom *params);
void			check_event(t_doom *p);
void			make_calculations(t_doom *params);
int				height_for_column(int x, t_doom *params);
void			route_events(t_doom *params);
void			parse_map(t_doom *params, char *raw_map);
void			add_perimeter_walls(int **map);
void			route_mouse_move(t_doom *params);
void			draw_sprites(t_doom *params);
void			draw_textured_wall(int x, int height, t_doom *params);
void			draw_textured_floor(int x, int height, t_doom *params);
void			draw_textured_ceiling(int x, int height, t_doom *params);
void			draw_hud(t_doom *params);
Uint32			set_color(int color, double dist);
int				calculate_start(int height, t_doom *params);
int				calculate_end(int height, t_doom *params);
void			load_sprites_textures(t_doom *params);
void			sprites_pickup(t_doom *params);
int				amount_clear(t_doom *params);
void			process_finish(t_doom *params);
void			jump(t_doom *params);
void			fly(t_doom *params);
void			squat(t_doom *params);
void			load_wall_textures(t_doom *params);
void			calc_cam_ray(int x, t_doom *params, t_iterations *iter);
void			key_down(int key, t_doom *params);
void			clear_all(t_doom *prm);

#endif
