/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:06:42 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:31:43 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	find_min_max(t_map *map, float (*x)[2], float (*y)[2], int i)
{
	if (map->pt_2d[i].u < (*x)[0])
		(*x)[0] = map->pt_2d[i].u;
	if (map->pt_2d[i].u > (*x)[1])
		(*x)[1] = map->pt_2d[i].u;
	if (map->pt_2d[i].v < (*y)[0])
		(*y)[0] = map->pt_2d[i].v;
	if (map->pt_2d[i].v > (*y)[1])
		(*y)[1] = map->pt_2d[i].v;
}

//x[0] and y[0] are min_x and min_y, the second indexes are the max
//we return the map sizes
float	*find_size(t_map *map)
{
	float	x[2];
	float	y[2];
	float	*result;
	int		i;

	x[0] = map->pt_2d[0].u;
	x[1] = x[0];
	y[0] = map->pt_2d[0].v;
	y[1] = y[0];
	result = (float *)malloc(4 * sizeof(float));
	if (!result)
		return (NULL);
	i = 0;
	while (i < map->size)
	{
		find_min_max(map, &x, &y, i);
		i++;
	}
	result[0] = x[0];
	result[1] = x[1];
	result[2] = y[0];
	result[3] = y[1];
	return (result);
}

float	find_scale(t_map *map, t_data *img)
{
	float	*scale;
	float	scale_x;
	float	scale_y;
	float	screen_scale;

	scale = find_size(map);
	if (!scale)
		return (-1);
	scale_x = ((float)img->x_win / (scale[1] - scale[0]));
	scale_y = ((float)img->y_win / (scale[3] - scale[2]));
	if (scale_x > scale_y)
		screen_scale = scale_y;
	else
		screen_scale = scale_x;
	return (free(scale), screen_scale);
}

void	error(t_map *map, t_var *screen, t_data *img)
{
	if (map->pt_2d)
		free(map->pt_2d);
	if (map->pt_3d)
		free(map->pt_3d);
	if (img->img)
		mlx_destroy_image(screen->mlx, img->img);
	if (screen->mlx_win)
		mlx_destroy_window(screen->mlx, screen->mlx_win);
	if (screen->mlx)
	{
		mlx_destroy_display(screen->mlx);
		free(screen->mlx);
	}
	exit(1);
}

//map.line_num - 1 cuz we wand to move the old data so before adding a line.
//only free(map.vectors) as we want to keep the content just free the ptr.
//null-terminates the map
t_3d	*map_realloc(t_map map, int new_size)
{
	t_3d	*new;
	int		old_len;

	if (!map.pt_3d)
		return (ft_calloc(new_size, sizeof(t_3d)));
	old_len = map.line_len * (map.line_num - 1);
	new = (t_3d *)ft_calloc(new_size, sizeof(t_3d));
	if (!new)
		return (NULL);
	ft_memmove(new, map.pt_3d, old_len * sizeof(t_3d));
	free(map.pt_3d);
	return (new);
}
