/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odindar <odindar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 05:52:56 by odindar           #+#    #+#             */
/*   Updated: 2026/05/13 05:52:56 by odindar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_list(t_list **list)
{
	t_list	*last;
	char	*buf;
	int		i;
	int		j;

	last = find_last_node(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	j = 0;
	while (last->content[i + j])
		j++;
	if (j == 0)
		return (free_list_and_save_rest(list, NULL));
	buf = malloc(sizeof(char) * (j + 1));
	if (!buf)
		return (free_list_and_save_rest(list, NULL));
	j = 0;
	while (last->content[i])
		buf[j++] = last->content[i++];
	buf[j] = '\0';
	free_list_and_save_rest(list, buf);
}

char	*extract_line(t_list *list)
{
	int		len;
	char	*line;

	if (!list)
		return (NULL);
	len = len_to_nextline(list);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	copy_str(list, line);
	return (line);
}

int	append_node(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buf);
		return (0);
	}
	new_node->content = buf;
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return (1);
	}
	last_node = find_last_node(*list);
	last_node->next = new_node;
	return (1);
}

void	read_to_list(int fd, t_list **list)
{
	char	*buf;
	int		bytes_read;

	while (!found_nextline(*list))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buf);
			if (bytes_read < 0)
				free_list_and_save_rest(list, NULL);
			return ;
		}
		buf[bytes_read] = '\0';
		if (!append_node(list, buf))
			return ;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_list_and_save_rest(&list, NULL);
		return (NULL);
	}
	read_to_list(fd, &list);
	if (!list)
		return (NULL);
	line = extract_line(list);
	clean_list(&list);
	return (line);
}
