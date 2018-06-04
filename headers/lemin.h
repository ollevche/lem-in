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

typedef struct	s_path
{
	int				id;
	int				*nodes;
	int				length;
	struct s_path	*next;
}				t_path;

/*
**	reading.c
*/

int				read_ants(void);
int				read_graph(t_room **rooms, t_link **links);

/*
**	struct_operations_N.c
*/

t_room			*get_room_by_id(t_room *rooms, int id);
t_room			*get_room_by_command(t_room *rooms, char *command);
int				add_strlist(t_strlist **head, char *str);
int				add_room(t_room **rooms, char *line,
							t_strlist **comments, char **command);
int				add_link(t_link **links, t_room *rooms, char *line,
							t_strlist **comments);
int				add_path(t_path **paths, int *nodes);

/*
**	display.c
*/

void			display_input(int ants, t_room *rooms, t_link *links);

/*
**	find_paths.c
*/

t_path			*find_paths(t_room *rooms, t_link *links);

/*
**	arrays.c
*/

int				arr_get_last(int *arr);
int				*new_arr(int size);

/*
**	free_structs.c
*/

void			free_strlist(t_strlist **list);
void			free_rooms(t_room **rooms);
void			free_links(t_link **links);
void			free_matrix(int ***matrix);
void			free_paths(t_path **paths);

/*
**	testing.c
*/

void			display_matrix(int **matrix, int size);


#endif
