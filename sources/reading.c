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

int		read_ants(void)
{
	int		ants;
	char	*line;
	int		i;
	int		zeros;

	line = safe_gnl(FILEDES);
	if (!line)
		return (ERROR_CODE);
	ants = 0;
	i = ft_strlen(line) - 1;
	zeros = 1;
	if (line[0] == '0')
		ants = ERROR_CODE;
	while (line[i] && ants != ERROR_CODE)
	{		
		ants += (line[i] - '0') * zeros;
		zeros *= 10;
		if (!ft_isdigit(line[i]))
			ants = ERROR_CODE;
		i--;
	}
	free(line);
	return (ants);
}

t_room	*read_rooms(void)
{
	return (NULL);
}

t_link	*read_links(void)
{
	return (NULL);
}