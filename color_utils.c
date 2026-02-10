/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:25:23 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:11:11 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//each number is shifted to its encoded position on the 32bit int.
//rgba vs argb depends on the graphics API. OpenGL is rgba 
static int	rgb_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

//linear interpolation gradient at moment t (t from 0.0 to 1)
// returns color at "instant t"
static int	lerp_color(int origin, int dest, float t)
{
	int	r[2];
	int	g[2];
	int	b[2];

	r[0] = get_red(origin);
	r[1] = get_red(dest);
	g[0] = get_green(origin);
	g[1] = get_green(dest);
	b[0] = get_blue(origin);
	b[1] = get_blue(dest);
	r[0] = r[0] + (r[1] - r[0]) * t;
	g[0] = g[0] + (g[1] - g[0]) * t;
	b[0] = b[0] + (b[1] - b[0]) * t;
	return (rgb_color(r[0], g[0], b[0]));
}

int	*gradient_array(int origin, int dest, int steps)
{
	int		*array;
	int		i;
	float	t;

	array = (int *)malloc((steps + 1) * sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	if (steps == 1)
	{
		array[i] = origin;
		return (array);
	}
	while (i < steps)
	{
		t = (float)i / (float)(steps - 1);
		array[i] = lerp_color(origin, dest, t);
		i++;
	}
	return (array);
}

static void	set_base_color(t_map *map, int steps)
{
	int	i;

	(void)steps;
	i = 0;
	while (i < map->size)
	{
		if (map->pt_3d[i].color == -2)
			map->pt_3d[i].color = 0x3408d1;
		i++;
	}
}

int	set_color(t_map *map, int col_switch)
{
	int	steps;
	int	i;
	int	z;

	steps = 0;
	i = 0;
	if (!col_switch)
	{
		steps = map->max_z - map->min_z;
		map->colors = gradient_array(0xffffff, 0xd1088b, steps + 1);
		if (!map->colors)
			return (0);
		i = 0;
		while (i < map->size)
		{
			z = (int)map->pt_3d[i].z;
			map->pt_3d[i].color = map->colors[z - map->min_z];
			i++;
		}
		free(map->colors);
		map->colors = NULL;
	}
	else
		set_base_color(map, steps);
	return (1);
}
