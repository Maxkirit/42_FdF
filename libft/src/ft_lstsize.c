/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:49:56 by mturgeon          #+#    #+#             */
/*   Updated: 2025/09/18 17:56:04 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*int main(void)
{
	t_list *test0 = ft_lstnew("this is a test");
	t_list *test1 = ft_lstnew("2nd string");
	t_list *test2 = ft_lstnew("3rd one");

	t_list **list = &test0;
	ft_lstadd_front(list, test1);
	ft_lstadd_front(list, test2);
	int size = ft_lstsize(*list);
	t_list **temp = list;
	int i = 0;
	while ((*temp))
	{
		printf("element (%d): %s\n", i, (char *)(*temp)->content);
		*temp = (*temp)->next;
		i++;
	}
	printf("size = %d\n", size);
    //printf("last elem: %s\n", (char *) (ft_lstlast(*list))->content);
}*/