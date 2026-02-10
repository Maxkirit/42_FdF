/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:01:49 by mturgeon          #+#    #+#             */
/*   Updated: 2025/10/23 15:35:10 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->num = content;
	new->next = NULL;
	return (new);
}
