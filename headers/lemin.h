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
	struct s_path	*prev;
	struct s_path	*next;
}				t_path;

typedef struct	s_set
{
	t_path			**paths;
	int				size;
	int				length;
	int				efficiency;
}				t_set;

// TODO: files - functions

int				read_ants(t_strlist **ants_cmnts);
int				read_graph(t_room **rooms, t_link **links);
t_room			*get_room_by_id(t_room *rooms, int id);
t_room			*get_room_by_command(t_room *rooms, char *command);
t_room			*get_room_by_name(t_room *rooms, char *name);
int				add_strlist(t_strlist **head, char *str);
int				add_room(t_room **rooms, char *line,
							t_strlist **comments, char **command);
int				add_link(t_link **links, t_room *rooms, char *line,
							t_strlist **comments);
int				add_path(t_path **paths, int *nodes);
t_path			*get_path_by_id(t_path *paths, int id);
void			display_input(t_strlist *ants_cmnts, int ants,
								t_room *rooms, t_link *links);
t_path			*get_paths(t_room *rooms, t_link *links);
int				*arr_n_copy(int *arr, int size);
int				*to_arr(int elem);
int				*arr_extend(int *arr, int elem);
int				arr_get_last_elem(int *arr);
int				arr_contains(int *nodes, int target);
int				*new_filled_arr(int size);
t_set			*get_set(t_path *all_paths, int ants, int rooms_num);
void			free_strlist(t_strlist **list);
void			free_rooms(t_room **rooms);
void			free_links(t_link **links);
void			free_matrix(int ***matrix);
void			free_paths(t_path **paths);
void			free_set(t_set **set);
void			terminate(t_room **rooms, t_link **links,
							t_strlist **ants_cmnts, t_set **set);
void    		total_free(t_room **rooms, t_link **links,
							t_strlist **ants_cmnts, t_set **set);
int 		    operation_failure(t_strlist *comments, char *command);

void			display_set(t_set *set);
void			display_paths(t_path *paths);

#endif
