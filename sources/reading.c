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

	if (!str || str[0] == '0')
		return (ERROR_CODE);
	i = ft_strlen(str) - 1;
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

int			read_ants(void)
{
	int		ants;
	char	*line;

	line = safe_gnl(FILEDES);
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

	i = 0;
	if (ft_strchr("#L", str[i]))
		return (0);
	while (str[i] && str[i] != ' ')
		if (str[i++] == '-')
			return (0);
	if (str[++i] == '0' && str[i + 1] != ' ')
		return (0);
	while (str[i] && str[i] != ' ')
		if (!ft_isdigit(str[i++]))
			return (0);
	if (str[++i] == '0' && str[i + 1] != 0)
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

static int	is_link(char *str, t_room *rooms)
{
	int		i;
	t_room	*iterator;

	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	iterator = rooms;
	while (iterator && ft_strncmp(str, iterator->name, i))
		iterator = iterator->next;
	if (!iterator)
	{
		ft_printf("not a link| case 1\n");
		return (0);
	}
	while (iterator && ft_strcmp(str + i + 1, iterator->name))
	{
		ft_printf("current:|%s|\ncomparing:|%s|\n", str + i + 1, iterator->name);
		iterator = iterator->next;
	}
	if (!iterator)
	{
		ft_printf("not a link| case 2\n");
		return (0);
	}
	return (1);
}

int			read_graph(t_room **rooms, t_link **links)
{
	char		*line;
	t_strlist	*comments;
	char		*command;
	int			ret_code;

	comments = NULL;
	command = NULL;
	ret_code = 0;
	while (ret_code != ERROR_CODE && (line = safe_gnl(FILEDES))) // when to stop?
	{
		if (line[0] == '#' && line[1] == '#')
			command = ft_strdup(line);
		else if (line[0] == '#')
			ret_code = add_strlist(&comments, ft_strdup(line));
		else if (is_room(line))
			ret_code = add_room(rooms, line, &comments, &command); // nulls
		else if (command)
			ret_code = ERROR_CODE;
		else if (is_link(line, *rooms))
			ret_code = add_link(links, *rooms, line, &comments); // nulls
		else
			ret_code = ERROR_CODE;//remove it
		free(line);
	}
	return (ret_code);
}
