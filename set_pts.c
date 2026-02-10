/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:24:05 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 20:01:17 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ANGLE 0.523599
#define COSF1 -0.86381960825f
#define SINF1 0.503801235f
#define SINF2 -0.99999034056f
#define COSF2 0.00439531264f

static void	which_proj(t_map *map, float *v, int *i)
{
	if (map->proj == 0)
	{
		map->pt_2d[*i].u = v[0] + v[1] * COSF1 + v[2] * COSF2;
		map->pt_2d[*i].v = v[0] + v[1] * SINF1 + v[2] * SINF2;
	}
	else
	{
		map->pt_2d[*i].u = v[0];
		map->pt_2d[*i].v = v[1];
	}
	return ;
}

//map->proj_bool == 0 is iso proj, else it's ortho
static void	proj_and_center(t_map *map)
{
	int		i;
	float	px;
	float	py;
	float	v[3];

	px = map->line_len / 2.0f;
	py = map->line_num / 2.0f;
	i = 0;
	while (i < map->size)
	{
		v[0] = map->pt_3d[i].x - px;
		v[1] = map->pt_3d[i].y - py;
		v[2] = map->z_scale * map->pt_3d[i].z;
		rotate(v, map);
		v[0] += px;
		v[1] += py;
		which_proj(map, v, &i);
		map->pt_2d[i].color = map->pt_3d[i].color;
		i++;
	}
	return ;
}

static int	init_bounds(t_map *map, t_data *img)
{
	float	*bounds;

	if (img->scale == -1.0f)
		img->scale = find_scale(map, img);
	if (img->scale == -1.0f)
		return (-1);
	bounds = find_size(map);
	if (!bounds)
		return (0);
	img->center_x = (bounds[1] + bounds[0]) / 2.0f;
	img->center_y = (bounds[3] + bounds[2]) / 2.0f;
	free(bounds);
	return (1);
}

int	projection(t_map *map, t_data *img)
{
	int		i;
	float	scale;
	int		result;

	if (!map->pt_2d)
	{
		map->pt_2d = (t_2d *)ft_calloc(map->size, sizeof(t_2d));
		if (!map->pt_2d)
			return (0);
	}
	proj_and_center(map);
	result = init_bounds(map, img);
	if (result <= 0)
		return (result);
	scale = img->scale * img->zoom;
	i = 0;
	while (i < map->size)
	{
		map->pt_2d[i].u = scale * (map->pt_2d[i].u - img->center_x)
			+ img->x_win / 2.0f;
		map->pt_2d[i].v = scale * (map->pt_2d[i].v - img->center_y)
			+ img->y_win / 2.0f;
		i++;
	}
	return (1);
}
