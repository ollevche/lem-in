/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:17:00 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:17:00 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		add_strlist(t_strlist **head, char *str)
{
	t_strlist	*new;

	if (!str)
		return (ERROR_CODE);
	new = (t_strlist*)malloc(sizeof(t_strlist));
	if (!new)
		return (ERROR_CODE);
	new->str = str;
	new->next = *head;
	new->prev = NULL;
	if (*head)
		(*head)->prev = new;
	*head = new;
	return (SUCCESS_CODE);
}
