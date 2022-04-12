/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_from.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 14:53:52 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "basics.h"

char	**gc_strarray_from(char **other, size_t size)
{
	size_t	i;
	char	**array;

	if (!other)
		return (gc_strarray_init());
	array = gc_calloc(size + 1, sizeof (char *));
	ft_memmove(array, other, size * sizeof (char *));
	i = 0;
	while (i < size)
	{
		array[i] = gc_strdup(other[i]);
		i++;
	}
	return (array);
}

char	**gct_strarray_from(char **other, size_t size)
{
	size_t	i;
	char	**array;

	if (!other)
		return (gct_strarray_init());
	array = gct_calloc(size + 1, sizeof(char *));
	ft_memmove(array, other, size * sizeof (char *));
	i = 0;
	while (i < size)
	{
		array[i] = gct_strdup(other[i]);
		i++;
	}
	return (array);
}
