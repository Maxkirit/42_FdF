/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:17:21 by mturgeon          #+#    #+#             */
/*   Updated: 2025/10/23 15:36:15 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void *toupper_str(void *str)
{
	char *dst = ft_strdup((const char *)str);
	char *temp = dst;
	while (*dst)
	{
		*dst = *dst - 32;
		dst++;
	}
	return (temp);
}

void ft_del(void *content)
{
	free(content);
	return ;
}
*/
t_list	*ft_lstmap(t_list *lst, int (*f)(int), void (*del)(int))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->num));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
int main(void)
{
	t_list *test0 = ft_lstnew("thisisatest");
	t_list *test1 = ft_lstnew("secondstring");
	t_list *test2 = ft_lstnew("thirdone");

	t_list **list = &test0;
	ft_lstadd_front(list, test1);
	ft_lstadd_front(list, test2);
	int size = ft_lstsize(*list);
	t_list *temp = *list;
	int i = 0;
	while (temp)
	{
		printf("element (%d): %s\n", i, (char *)temp->content);
		temp = temp->next;
		i++;
	}
	printf("size = %d\n", size);
    t_list *last = ft_lstnew("blablabla");
    ft_lstadd_back(list, last);
    printf("last elem: %s\n", (char *) (ft_lstlast(*list))->content);

	t_list *dst = ft_lstmap(*list, toupper_str, ft_del);
	t_list *tmp = dst;
	i = 0;
	while (tmp)
	{
		printf("element (%d): %s\n", i, (char *) tmp->content);
		tmp = tmp->next;
		i++;
	}
}*/