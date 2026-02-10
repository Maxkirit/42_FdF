/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:07:24 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 16:38:37 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_red(int color)
{
	return (((color) >> 16) & 0xFF);
}

int	get_green(int color)
{
	return (((color) >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return ((color) & 0xFF);
}

int	find_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}
