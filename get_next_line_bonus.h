/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:28:01 by paranha           #+#    #+#             */
/*   Updated: 2023/12/07 18:08:32 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	size_t			length;
	struct s_list	*next;
}					t_list;

void				enqueue(t_list **lst, t_list *new);
void				*ft_memcpy(void *dest, const void *src, size_t n);
t_list				*get_tail(t_list *lst);
t_list				*create_node(char *content);
t_list				*cleanup_on_error(t_list **stash, t_list *new,
						int bytes_read);
char				*get_next_line(int fd);

#endif
