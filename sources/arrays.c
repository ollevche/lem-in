/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:44:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 18:44:25 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	arr_get_last(int *arr)
{
	int i;

	i = 0;
	while (arr[i + 1] != -1)
		i++;
	return (i);
}

int	*new_arr(int size)
{
	int	*arr;
	int	i;

	arr = (int*)malloc(sizeof(int) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size + 1)
		cur_path[i++] = -1;

}