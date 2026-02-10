/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:44:26 by mturgeon          #+#    #+#             */
/*   Updated: 2025/11/10 15:30:19 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

int	split_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && *tab[i] != '\n')
		i++;
	return (i);
}

int	return_error(void)
{
	ft_printf("enter 1 arg only, a path to .fdf file.\n");
	return (1);
}

static int	find_in_base(char c)
{
	char	base[17];
	int		i;
	int		offset;

	base[16] = '\0';
	i = 0;
	offset = 48;
	while (i < 16)
	{
		if (i == 10)
			offset = 55;
		base[i] = i + offset;
		i++;
	}
	i = 0;
	while (base[i])
	{
		if (base[i] == c || ft_tolower(base[i]) == c)
			return (i);
		i++;
	}
	return (-1);
}

//returns -1 if no color or error in formatting
int	atoi_16(char *nbr)
{
	int	result;
	int	i;
	int	digit;

	if (!nbr)
		return (-2);
	result = 0;
	i = 0;
	while (nbr[i] == '0' || nbr[i] == 'x')
		i++;
	while (nbr[i])
	{
		digit = find_in_base(nbr[i]);
		if (digit == -1)
			return (-1);
		result = result * 16 + digit;
		i++;
	}
	return (result);
}
