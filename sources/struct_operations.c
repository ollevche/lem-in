/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:20:49 by ollevche          #+#    #+#             */
/*   Updated: 2018/05/31 17:20:49 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		add_strlist(t_strlist **head, char *str)
{
	t_strlist	*iterator;
	t_strlist	*new_elem;

	new_elem = (t_strlist*)malloc(sizeof(t_strlist));
	if (!new_elem)
		return (ERROR_CODE);
	new_elem->str = str;
	if (!*head)
		*head = new_elem;
	else
	{
		iterator = *head;
		while (iterator->next)
			iterator = iterator->next;
		iterator->next = new_elem;
	}
	return (SUCCESS_CODE);
}

