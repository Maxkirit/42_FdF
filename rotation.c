/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:02:50 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:21:37 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	rotate_x(float v[3], t_map *map)
{
	float	y;
	float	z;

	y = v[1];
	z = v[2];
	v[1] = y * cosf(map->angle_x) - z * sinf(map->angle_x);
	v[2] = y * sinf(map->angle_x) + z * cosf(map->angle_x);
}

static void	rotate_y(float v[3], t_map *map)
{
	float	x;
	float	z;

	x = v[0];
	z = v[2];
	v[0] = x * cosf(map->angle_y) + z * sinf(map->angle_y);
	v[2] = -x * sinf(map->angle_y) + z * cosf(map->angle_y);
}

static void	rotate_z(float v[3], t_map *map)
{
	float	x;
	float	y;

	x = v[0];
	y = v[1];
	v[0] = x * cosf(map->angle_z) - y * sinf(map->angle_z);
	v[1] = x * sinf(map->angle_z) + y * cosf(map->angle_z);
}

void	rotate(float v[3], t_map *map)
{
	if (map->angle_x || map->angle_y || map->angle_z)
	{
		rotate_z(v, map);
		rotate_y(v, map);
		rotate_x(v, map);
	}
	return ;
}

//guarantees pixel is put in right place by adding offset 
//for data alignement to addess;
//data->adrress is top left of image
void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->address + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
