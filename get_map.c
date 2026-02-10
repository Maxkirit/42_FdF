/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:00:12 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:06:24 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	set_line_len(t_map *map, char **xyz)
{
	int	new_line_len;
	int	i;

	new_line_len = split_len(xyz);
	i = 0;
	while (xyz[new_line_len - 1][i])
	{
		if (xyz[new_line_len - 1][i] == '\n')
			xyz[new_line_len - 1][i] = '\0';
		i++;
	}
	if (xyz[new_line_len] && xyz[new_line_len][0] == '\n')
	{
		free(xyz[new_line_len]);
		xyz[new_line_len] = NULL;
	}
	if (map->line_len && new_line_len != map->line_len)
		return (-1);
	map->line_len = new_line_len;
	map->line_num++;
	map->pt_3d = map_realloc(*map, map->line_len * map->line_num + 1);
	if (!map->pt_3d)
		return (0);
	return (1);
}

static int	set_z_and_col(int *start, int *i, char **pt_col, t_map *map)
{
	char	*temp;

	map->pt_3d[*start + *i].z = (float)ft_atoi(pt_col[0]);
	temp = ft_itoa(map->pt_3d[*start + *i].z);
	if (!temp)
		return (0);
	if (ft_strncmp(pt_col[0], temp, ft_strlen(pt_col[0])))
		return (free_split((void **)pt_col), free(temp), -1);
	free(temp);
	if (map->pt_3d[*start + *i].z < map->min_z)
		map->min_z = roundf(map->pt_3d[*start + *i].z);
	if (map->pt_3d[*start + *i].z > map->max_z)
		map->max_z = roundf(map->pt_3d[*start + *i].z);
	return (1);
}

static int	set_vect(char **xyz, int *i, t_map *map, int *col_switch)
{
	int		start;
	char	**pt_col;

	pt_col = ft_split(xyz[*i], ',');
	if (!pt_col)
		return (0);
	start = map->line_len * (map->line_num - 1);
	map->pt_3d[start + *i].x = (float)*i;
	map->pt_3d[start + *i].y = (float)map->line_num - 1;
	map->pt_3d[start + *i].z = (float)ft_atoi(pt_col[0]);
	if (!set_z_and_col(&start, i, pt_col, map))
		return (0);
	map->pt_3d[start + *i].color = atoi_16(pt_col[1]);
	if (map->pt_3d[start + *i].color != -2)
		*col_switch = 1;
	free_split((void **)pt_col);
	*i += 1;
	return (1);
}

static void	parsing_logic(t_map *map, char **xyz, int fd, int *col_switch)
{
	int	i;
	int	result;

	result = set_line_len(map, xyz);
	error_handle(result, map, xyz, fd);
	i = 0;
	while (xyz[i])
	{
		result = set_vect(xyz, &i, map, col_switch);
		error_handle(result, map, xyz, fd);
	}
	free(map->line);
	free_split((void **)xyz);
	map->line = get_next_line(fd);
}

t_map	parse_map(int fd)
{
	t_map	map;
	char	**xyz;
	int		col_switch;

	col_switch = 0;
	init_map(&map);
	map.line = get_next_line(fd);
	if (!map.line)
		exit(1);
	while (map.line)
	{
		xyz = ft_split(map.line, ' ');
		if (!xyz)
			map_error(map.line, NULL, map.pt_3d, fd);
		parsing_logic(&map, xyz, fd, &col_switch);
	}
	map.size = map.line_len * map.line_num;
	free(map.line);
	if (!set_color(&map, col_switch))
		map_error(NULL, NULL, map.pt_3d, fd);
	close (fd);
	return (map);
}
