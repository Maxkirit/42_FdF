/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:52:12 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 20:00:41 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int	key_handle_surplus(int keycode, t_pack *pack)
{
	if (keycode == 65362)
		pack->map->angle_x += 0.1f;
	if (keycode == 65364)
		pack->map->angle_x -= 0.1f;
	if (keycode == 61)
		pack->map->angle_y += 0.1f;
	if (keycode == 45)
		pack->map->angle_y -= 0.1f;
	if (keycode == 65363)
		pack->map->angle_z += 0.1f;
	if (keycode == 65361)
		pack->map->angle_z -= 0.1f;
	if (keycode == 119)
		pack->img->center_y -= 0.7f;
	if (keycode == 97)
		pack->img->center_x -= 0.7f;
	if (keycode == 115)
		pack->img->center_y += 0.7f;
	if (keycode == 100)
		pack->img->center_x += 0.7f;
	if (keycode == 65451)
		pack->img->zoom += 0.05f;
	if (keycode == 65453)
		pack->img->zoom -= 0.05f;
	return (1);
}

//free everything before exiting
static int	key_handle(int keycode, t_pack *pack)
{
	if (keycode == 65307)
		end_program(pack);
	if (keycode == 49)
		pack->map->proj = 0;
	if (keycode == 50)
		pack->map->proj = 1;
	if (keycode == 119)
		pack->img->scale = -1.0f;
	if (keycode == 97)
		pack->img->scale = -1.0f;
	if (keycode == 115)
		pack->img->scale = -1.0f;
	if (keycode == 100)
		pack->img->scale = -1.0f;
	key_handle_surplus(keycode, pack);
	draw(pack->map, pack->screen, pack->img);
	return (0);
}

static int	mouse_handle(int button, int x, int y, t_pack *pack)
{
	(void)x;
	(void)y;
	if (button == 5)
	{
		if (pack->map->z_scale >= 0.05f)
			pack->map->z_scale -= 0.05f;
	}
	if (button == 4)
		pack->map->z_scale += 0.05f;
	draw(pack->map, pack->screen, pack->img);
	return (0);
}

int	close_with_x(t_pack *pack)
{
	end_program(pack);
	return (1);
}

void	init_mlx(t_pack *pack, int screen_x, int screen_y)
{
	pack->img->x_win = screen_x;
	pack->img->y_win = screen_y;
	pack->img->zoom = 0.9f;
	pack->img->scale = -1.0f;
	pack->img->center_x = -1.0f;
	pack->img->center_y = -1.0f;
	pack->screen->mlx = mlx_init();
	if (!pack->screen->mlx)
	{
		free(pack->map->pt_2d);
		free(pack->map->pt_3d);
		error(pack->map, pack->screen, pack->img);
	}
	pack->screen->mlx_win = mlx_new_window(pack->screen->mlx, pack->img->x_win,
			pack->img->y_win, "~.FdF.~");
	if (!pack->screen->mlx_win)
	{
		free(pack->map->pt_2d);
		free(pack->map->pt_3d);
		error(pack->map, pack->screen, pack->img);
	}
	mlx_key_hook(pack->screen->mlx_win, key_handle, pack);
	mlx_mouse_hook(pack->screen->mlx_win, mouse_handle, pack);
	mlx_hook(pack->screen->mlx_win, 17, 0, close_with_x, pack);
}
