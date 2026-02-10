/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:43:09 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 19:56:10 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <fcntl.h>

# include "libft/src/libft.h"
# include "mlx_linux/mlx.h"

//macros to extract colour part of a colour. values encoded in uint8_t
//RGBA on macos therefore alpha last
# define PI 3.14159

typedef struct s_3d
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_3d;

typedef struct s_2d
{
	float	u;
	float	v;
	int		rnd_u;
	int		rnd_v;
	int		color;
}	t_2d;

typedef struct s_data
{
	void	*img;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		x_win;
	int		y_win;
	float	zoom;
	float	scale;
	float	center_x;
    // float   inc_x;
	float	center_y;
    // float   inc_y;
}	t_data;

typedef struct s_var
{
	void	*mlx;
	void	*mlx_win;
}	t_var;

typedef struct s_map
{
	t_3d	*pt_3d;
	t_2d	*pt_2d;
	int		size;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	float	z_scale;
	int		min_z;
	int		max_z;
	int		line_len;
	int		line_num;
	int		*colors;
	char	*line;
	int		proj;
}	t_map;

typedef struct s_pack
{
	t_map	*map;
	t_var	*screen;
	t_data	*img;
}	t_pack;

typedef struct s_pts
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;
	int	color;
	int	steps;
	int	color_step;
}	t_pts;

int			get_red(int color);
int			get_green(int color);
int			get_blue(int color);
int			*gradient_array(int origin, int dest, int steps);
void		free_split(void **tab);
int			split_len(char **tab);
t_map		parse_map(int fd);
void		my_pixel_put(t_data *data, int x, int y, int color);
void		init_mlx(t_pack *pack, int screen_x, int screen_y);
int			close_with_x(t_pack *pack);
int			return_error(void);
int			atoi_16(char *nbr);
void		set_pts(t_map *map);
int			draw_lines_to_img(t_map *map, t_var *screen, t_data *img);
int			draw(t_map *map, t_var *screen, t_data *img);
float		find_scale(t_map *map, t_data *img);
float		*find_size(t_map *map);
void		rotate(float v[3], t_map *map);
int			projection(t_map *map, t_data *img);
int			set_color(t_map *map, int col_switch);
void		error(t_map *map, t_var *screen, t_data *img);
t_3d		*map_realloc(t_map map, int new_size);
void		end_program(t_pack *pack);
void		map_error(char *line, char **xyz, t_3d *pt_3d, int fd);
void		error_handle(int result, t_map *map, char **xyz, int fd);
void		init_map(t_map *map);
int			*set_dest_col(t_2d *pt_0, t_2d *pt_1, t_pts *pts);
int			find_max(int a, int b);

#endif