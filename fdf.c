/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:37:01 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:03:43 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	draw(t_map *map, t_var *screen, t_data *img)
{
	if (!projection(map, img))
		return (0);
	if (!draw_lines_to_img(map, screen, img))
		return (0);
	return (1);
}

int	fdf(t_map map)
{
	t_var	screen;
	t_data	img;
	t_pack	pack;

	pack.img = &img;
	pack.screen = &screen;
	pack.map = &map;
	init_mlx(&pack, 3000, 2000);
	if (!draw(&map, &screen, &img))
		error(&map, &screen, &img);
	mlx_loop(screen.mlx);
	mlx_destroy_window(screen.mlx, screen.mlx_win);
	mlx_destroy_display(screen.mlx);
	free(screen.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**test_input;
	int		fd;
	t_map	map;

	if (argc != 2)
		return_error();
	test_input = ft_split(argv[1], '.');
	if (!test_input)
		return (1);
	if (!test_input[1])
		return (free_split((void **)test_input), return_error());
	if (ft_strncmp("fdf", test_input[1], ft_strlen(test_input[1])))
		return (free_split((void **)test_input), return_error());
	free_split((void **)test_input);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("wrong file path\n");
		return (1);
	}
	map = parse_map(fd);
	fdf(map);
	return (0);
}
