/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:01:25 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/23 18:01:25 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define ERROR_CODE -1
# define SUCCESS_CODE 1
# define FILEDES STDIN_FILENO

# include "libftprintf.h"
# include <stdbool.h>
# include <errno.h>

typedef struct	s_strlist
{
	char				*str;
	struct s_strlist	*prev;
	struct s_strlist	*next;
}				t_strlist;

typedef struct	s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	t_strlist		*comments;
	char			*command;
	struct s_room	*prev;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	int				from;
	int				to;
	t_strlist		*comments;
	struct s_link	*prev;
	struct s_link	*next;
}				t_link;

/*
**	reading.c
*/

int				read_ants(void);
int				read_graph(t_room **rooms, t_link **links);

/*
**	struct_operations.c
*/

t_room			*get_room(t_room *rooms, int id);
int				add_strlist(t_strlist **head, char *str);
int				add_room(t_room **rooms, char *line,
							t_strlist **comments, char **command);
int				add_link(t_link **links, t_room *rooms, char *line,
							t_strlist **comments);

/*
**	free_structs.c
*/

void			free_strlist(t_strlist *list);
void			free_rooms(t_room *rooms);
void			free_links(t_link *links);

#endif
