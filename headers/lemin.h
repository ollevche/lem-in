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
# include <limits.h>
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

int				read_ants(t_strlist **ants_cmnts);
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
t_path  		*get_path_by_id(t_path *paths, int id);

/*
**	display.c
*/

void			display_input(t_strlist *ants_cmnts, int ants, t_room *rooms, t_link *links);

/*
**	get_paths.c
*/

t_path			*get_paths(t_room *rooms, t_link *links);

/*
**	arrays.c
*/

int				*arr_n_copy(int *arr, int size);
int				*to_arr(int elem);
int				*arr_extend(int *arr, int elem);
int				arr_get_last_elem(int *arr);
int				arr_contains(int *nodes, int target);

/*
**	get_set.c
*/

int				*get_set(t_path *all_paths, int ants);

/*
**	advanced_arrays.c
*/

int				max_len(int *paths_ids, t_path *paths);
int				len_of_paths(int *paths_ids, t_path *paths);

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

void			display_matrix(int **matrix);
void			display_paths(t_path *paths, t_room *rooms);
void			display_set(int *set, int efficiency);

#endif
