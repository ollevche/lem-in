/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:03:10 by ollevche          #+#    #+#             */
/*   Updated: 2018/05/31 13:03:11 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	to_pos_int(char *str)
{
	int	i;
	int	zeros;
	int	res;

	i = ft_strlen(str) - 1;
	if (!str || i == -1 || str[0] == '0')
		return (ERROR_CODE);
	zeros = 1;
	res = 0;
	while (i > -1)
	{
		if (!ft_isdigit(str[i]))
			return (ERROR_CODE);
		res += (str[i] - '0') * zeros;
		zeros *= 10;
		i--;
	}
	return (res);
}

int			read_ants(t_strlist **ants_cmnts)
{
	int		ants;
	char	*line;

	ants = 0;
	while ((line = safe_gnl(FILEDES)) && line[0] == '#')
	{
		if (addslst(ants_cmnts, line) == ERROR_CODE)
			ants = -1;
		if (line[1] == '#')
		{
			line = safe_gnl(FILEDES);
			break ;
		}
	}
	if (!ants)
		ants = to_pos_int(line);
	free(line);
	return (ants);
}

/*
**	'-', '#', 'L' in room name are forbidden
*/

static int	is_room(char *str)
{
	int		i;

	if (!str)
		return (false);
	i = 0;
	if (ft_strchr("#L", str[0]))
		return (false);
	while (str[i] && str[i] != ' ')
		if (ft_strchr("- ", str[i++]))
			return (false);
	if (!str[i] || (str[++i] == '0' && str[i + 1] != ' '))
		return (false);
	while (str[i] && str[i] != ' ')
		if (!ft_isdigit(str[i++]))
			return (false);
	if (!str[i] || (str[++i] == '0' && str[i + 1] != 0))
		return (false);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] || (!str[i] && str[i - 1] == ' '))
		return (false);
	return (true);
}

static int	is_link(char *str, t_room *rooms)
{
	int		i;
	t_room	*iterator;

	if (!str)
		return (false);
	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	iterator = rooms;
	while (iterator && (ft_strlen(iterator->name) != (size_t)i
						|| ft_strncmp(str, iterator->name, i)))
		iterator = iterator->next;
	if (!iterator)
		return (false);
	iterator = rooms;
	while (iterator && ft_strcmp(str + i + 1, iterator->name))
		iterator = iterator->next;
	if (!iterator)
		return (false);
	return (true);
}

/*
**	line of read_graph function which copies the line into the command:
**	ret_code = (command = ft_strdup(line)) ? SUCCESS_CODE : ERROR_CODE;
**	...
**	it's modified because of The Norme :(
*/

int			read_graph(t_room **rooms, t_link **links)
{
	char		*line;
	t_strlist	*cmnts;
	char		*cmnd;
	int			ret_c;

	cmnts = NULL;
	cmnd = NULL;
	ret_c = SUCCESS_CODE;
	while (ret_c == SUCCESS_CODE)
	{
		if (is_room((line = safe_gnl(FILEDES))))
			ret_c = add_room(rooms, line, &cmnts, &cmnd);
		else if (is_link(line, *rooms) && addslst(&cmnts, cmnd) && !(cmnd = 0))
			ret_c = add_link(links, *rooms, line, &cmnts);
		else if (cmnd)
			ret_c = ERROR_CODE;
		else if (line && line[0] == '#' && line[1] == '#')
			cmnd = ft_strdup(line);
		else if (line && line[0] == '#')
			ret_c = addslst(&cmnts, ft_strdup(line));
		else
			ret_c = -2;
		free_rg(&line, ret_c != 1 ? &cmnd : 0, ret_c != 1 ? &cmnts : 0);
	}
	return (ret_c == ERROR_CODE ? ERROR_CODE : SUCCESS_CODE);
}
