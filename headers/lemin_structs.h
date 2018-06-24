/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:44:32 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/15 16:44:32 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_STRUCTS_H
# define LEMIN_STRUCTS_H

# include "lemin.h"

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
	int				*ants;
	int				size;
	int				length;
	int				efficiency;
	t_path			*shortest_path_ever;
	int				total_rooms;
}				t_set;

#endif
