/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:32:03 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 16:37:56 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	end_program(t_pack *pack)
{
	if (pack->map->pt_2d)
		free(pack->map->pt_2d);
	if (pack->map->pt_3d)
		free(pack->map->pt_3d);
	if (pack->screen->mlx_win)
		mlx_destroy_window(pack->screen->mlx, pack->screen->mlx_win);
	if (pack->screen->mlx)
	{
		mlx_destroy_display(pack->screen->mlx);
		free(pack->screen->mlx);
	}
	exit(0);
}

//iterating over gnl to free the static buffer
void	map_error(char *line, char **xyz, t_3d *pt_3d, int fd)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (xyz)
		free_split((void **)xyz);
	if (pt_3d)
		free(pt_3d);
	exit(1);
}

void	error_handle(int result, t_map *map, char **xyz, int fd)
{
	if (result <= 0)
	{
		if (result == -1)
			ft_printf("wrong map input\n");
		map_error(map->line, xyz, map->pt_3d, fd);
	}
	return ;
}

void	init_map(t_map *map)
{
	map->line_len = 0;
	map->line_num = 0;
	map->angle_x = 0.0f;
	map->angle_y = 0.0f;
	map->angle_z = 0.0f;
	map->z_scale = 0.2f;
	map->min_z = INT32_MAX;
	map->max_z = INT32_MIN;
	map->proj = 0;
	map->pt_2d = NULL;
	map->pt_3d = NULL;
	map->colors = NULL;
	map->line = NULL;
}

int	*set_dest_col(t_2d *pt_0, t_2d *pt_1, t_pts *pts)
{
	int	*dest_col;

	if (pt_0->color == pt_1->color)
	{
		dest_col = malloc(sizeof(int));
		if (!dest_col)
			return (NULL);
		dest_col[0] = pt_0->color;
	}
	else
	{
		dest_col = gradient_array(pt_0->color, pt_1->color, pts->steps + 1);
		if (!dest_col)
			return (NULL);
	}
	return (dest_col);
}
