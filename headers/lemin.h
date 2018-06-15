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
# include "lemin_structs.h"
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

extern int g_log;

/*
**	reading.c
*/

int				read_ants(t_strlist **ants_cmnts);
int				read_graph(t_room **rooms, t_link **links);

/*
**	display.c
*/

void			display_input(t_strlist *ants_cmnts, int ants,
								t_room *rooms, t_link *links);

/*
**	get_paths.c
*/

t_path			*get_paths(t_room *rooms, t_link *links);

/*
**	get_set.c
*/

t_set			*get_set(t_path *all_paths, int ants, int rooms_num);

/*
**	pick_set.c
*/

int				pick_set(t_set *set, t_path *paths, int rooms_num);

/*
**	arrays.c
*/

int				*arr_n_copy(int *arr, int size);
int				*to_arr(int elem);
int				*arr_extend(int *arr, int elem);
int				arr_get_last_elem(int *arr);
int				*new_filled_arr(int size);

/*
**	ops_room.c
*/

t_room			*get_room_by_id(t_room *rooms, int id);
t_room			*get_room_by_command(t_room *rooms, char *command);
t_room			*get_room_by_name(t_room *rooms, char *name);
int				add_room(t_room **rooms, char *line,
							t_strlist **comments, char **command);

/*
**	ops_link.c
*/

int				add_link(t_link **links, t_room *rooms, char *line,
							t_strlist **comments);

/*
**	ops_path.c
*/

int				add_path(t_path **paths, int *nodes);
t_path			*get_path_by_id(t_path *paths, int id);

/*
**	ops_set.c
*/

int				max_len(t_set *set);
t_path			**new_set_paths(int size, t_path *paths);
t_path			**set_paths_copy(t_path **set_paths, int size);
int				len_of_set_paths(t_path **set_paths);
t_set			*new_set(int size);

/*
**	ops_other.c
*/

int				add_strlist(t_strlist **head, char *str);

/*
**	util.c
*/

void			terminate(t_room **rooms, t_link **links,
							t_strlist **ants_cmnts, t_set **set);
int				operation_failure(t_strlist *comments, char *command);

/*
**	free_structs.c
*/

void			free_strlist(t_strlist **list);
void			free_rooms(t_room **rooms);
void			free_links(t_link **links);
void			free_paths(t_path **paths);
void			free_set(t_set **set);

/*
**	free_other.c
*/

void			free_matrix(int ***matrix);
void			total_free(t_room **rooms, t_link **links,
							t_strlist **ants_cmnts, t_set **set);

/*
**	debug.c
*/

void			display_set(char *title, t_set *set);
void			display_paths(char *title, t_path *paths, t_room *rooms);

#endif
