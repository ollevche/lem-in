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

# define ERROR_ID -1;

# include "libftprintf.h"

typedef struct	s_room
{
	int		id;
	char	*name;
	int		x;
	int		y;
	char	is_empty;
	t_room	*next;
}				t_room;

typedef struct	s_link
{
	int		from;
	int		to;
	char	is_burned;
	t_link	*next;
}				t_link;

#endif
