/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:15:48 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:01:00 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	*init_pts(t_pts *pts, t_2d pt_0, t_2d pt_1)
{
	pts->dx = abs(pt_1.rnd_u - pt_0.rnd_u);
	pts->dy = -abs(pt_1.rnd_v - pt_0.rnd_v);
	pts->steps = find_max(pts->dx, -pts->dy);
	if (pt_0.rnd_u < pt_1.rnd_u)
		pts->sx = 1;
	else
		pts->sx = -1;
	if (pt_0.rnd_v < pt_1.rnd_v)
		pts->sy = 1;
	else
		pts->sy = -1;
	pts->error = pts->dx + pts->dy;
	return (set_dest_col(&pt_0, &pt_1, pts));
}

static int	indent_error(t_pts *pts, t_2d *pt_0, t_2d *pt_1, int *col_table)
{
	if (pts->e2 >= pts->dy)
	{
		if (pt_0->rnd_u == pt_1->rnd_u)
			return (free(col_table), 1);
		pts->error += pts->dy;
		pt_0->rnd_u += pts->sx;
	}
	if (pts->e2 <= pts->dx)
	{
		if (pt_0->rnd_v == pt_1->rnd_v)
			return (free(col_table), 1);
		pts->error += pts->dx;
		pt_0->rnd_v += pts->sy;
	}
	return (0);
}

int	plot_line(t_2d pt_0, t_2d pt_1, t_data *img)
{
	t_pts	pts;
	int		*col_table;
	int		print_col;

	pts.color_step = 0;
	col_table = init_pts(&pts, pt_0, pt_1);
	if (!col_table)
		return (0);
	if (pt_0.color == pt_1.color)
		print_col = pt_1.color;
	while (1)
	{
		if (pt_0.color != pt_1.color)
		{
			pts.color_step++;
			print_col = col_table[pts.color_step];
		}
		if ((pt_0.rnd_u > 0 && pt_0.rnd_u < img->x_win)
			&& (pt_0.rnd_v > 0 && pt_0.rnd_v < img->y_win))
			my_pixel_put(img, pt_0.rnd_u, pt_0.rnd_v, print_col);
		pts.e2 = 2 * pts.error;
		if (indent_error(&pts, &pt_0, &pt_1, col_table))
			return (1);
	}
	return (free(col_table), 0);
}

int	draw_lines(t_map *map, t_data *img)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
		map->pt_2d[i].rnd_u = roundf(map->pt_2d[i].u);
		map->pt_2d[i].rnd_v = roundf(map->pt_2d[i].v);
		i++;
	}
	i = 0;
	while (i < map->size)
	{
		if ((i + 1) % map->line_len != 0)
			if (!plot_line(map->pt_2d[i], map->pt_2d[i + 1], img))
				return (0);
		if ((i + map->line_len) < (map->line_len * map->line_num))
			if (!plot_line(map->pt_2d[i], map->pt_2d[i + map->line_len], img))
				return (0);
		i++;
	}
	return (1);
}

//mlx_new_img each time a pixel changes.
int	draw_lines_to_img(t_map *map, t_var *screen, t_data *img)
{
	img->img = mlx_new_image(screen->mlx, img->x_win, img->y_win);
	if (!img)
		return (0);
	img->address = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	if (!img->address)
		return (0);
	if (!draw_lines(map, img))
	{
		mlx_destroy_image(screen->mlx, img->img);
		return (0);
	}
	mlx_put_image_to_window(screen->mlx, screen->mlx_win, img->img, 0, 0);
	mlx_destroy_image(screen->mlx, img->img);
	return (1);
}
