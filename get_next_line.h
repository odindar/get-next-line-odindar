/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odindar <odindar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 04:31:00 by odindar           #+#    #+#             */
/*   Updated: 2026/05/13 04:31:00 by odindar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	read_to_list(int fd, t_list **list);
int		append_node(t_list **list, char *buf);
char	*extract_line(t_list *list);
void	clean_list(t_list **list);
int		found_nextline(t_list *list);
t_list	*find_last_node(t_list *list);
int		len_to_nextline(t_list *list);
void	copy_str(t_list *list, char *line);
void	free_list_and_save_rest(t_list **list, char *buf);

#endif
