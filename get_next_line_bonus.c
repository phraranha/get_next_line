/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:23:47 by paranha           #+#    #+#             */
/*   Updated: 2023/12/07 17:11:37 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	check_for_newline(t_list *stash);
static void		read_and_store(t_list **stash, int fd);
static void		cat_content(t_list *stash, char **line);
static void		trim_tail(t_list **stash, size_t counter);

char	*get_next_line(int fd)
{
	static t_list	*stash[OPEN_MAX];
	char			*line;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_store(&stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	cat_content(stash[fd], &line);
	trim_tail(&stash[fd], 0);
	return (line);
}

static size_t	check_for_newline(t_list *stash)
{
	char	*content;
	size_t	counter;

	stash = get_tail(stash);
	if (!stash)
		return (0);
	content = stash->content;
	counter = 0;
	while (content[counter] && content[counter] != '\n')
		++counter;
	stash->length = counter + (content[counter] == '\n');
	return (content[counter] == '\n');
}

static void	read_and_store(t_list **stash, int fd)
{
	int		bytes_read;
	t_list	*new;

	bytes_read = 0;
	while (!check_for_newline(*stash))
	{
		new = create_node(malloc(sizeof(char) * (BUFFER_SIZE + 1)));
		bytes_read = read(fd, new->content, BUFFER_SIZE);
		new = cleanup_on_error(stash, new, bytes_read);
		if (!new)
			return ;
		new->content[bytes_read] = '\0';
		new->length = bytes_read;
		enqueue(stash, new);
	}
}

static void	cat_content(t_list *stash, char **line)
{
	size_t	line_size;
	t_list	*current;

	line_size = 0;
	current = stash;
	while (current)
	{
		line_size += current->length;
		current = current->next;
	}
	*line = malloc(sizeof(**line) * (line_size + 1));
	line_size = 0;
	current = stash;
	while (current)
	{
		ft_memcpy(*line + line_size, current->content, current->length);
		line_size += current->length;
		current = current->next;
	}
	(*line)[line_size] = '\0';
}

static void	trim_tail(t_list **stash, size_t slice_position)
{
	t_list	*current;
	t_list	*new;
	char	*content;
	size_t	size;

	current = get_tail(*stash);
	content = current->content;
	size = current->length;
	current->content = NULL;
	cleanup_on_error(stash, NULL, -1);
	if (content[size])
	{
		while (content[size])
		{
			content[slice_position] = content[size];
			slice_position++;
			size++;
		}
		content[slice_position] = '\0';
		new = create_node(content);
		enqueue(stash, new);
	}
	else
		free(content);
}
