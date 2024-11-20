/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:11:35 by paranha           #+#    #+#             */
/*   Updated: 2023/12/07 17:12:00 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

t_list	*create_node(char *content)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->length = 0;
	new->next = NULL;
	return (new);
}

t_list	*get_tail(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	enqueue(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
		get_tail(*lst)->next = new;
}

t_list	*cleanup_on_error(t_list **stash, t_list *new, int bytes_read)
{
	t_list	*tmp;

	if (bytes_read <= 0)
	{
		if (new)
		{
			free(new->content);
			free(new);
		}
		if (bytes_read < 0)
		{
			if (!stash)
				return (NULL);
			while (*stash)
			{
				tmp = *stash;
				*stash = (*stash)->next;
				free(tmp->content);
				free(tmp);
			}
		}
		return (NULL);
	}
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destiny;
	unsigned char	*source;

	i = 0;
	destiny = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		destiny[i] = source[i];
		i++;
	}
	return (dest);
}
