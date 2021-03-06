/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_asstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 15:23:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

static void	copy_into_str(char **array, size_t arr_size, char *str);

char	*gct_strarray_asstr(char **array)
{
	size_t	i;
	size_t	arr_size;
	size_t	total_size;
	char	*str;

	if (!array || gc_strarray_size(array) == 0)
		return (gct_strdup(""));
	arr_size = gc_strarray_size(array);
	total_size = 0;
	i = 0;
	while (i < arr_size)
	{
		total_size += gc_strlen(array[i]) + 1;
		i++;
	}
	str = gct_calloc(total_size, sizeof(char));
	if (!str)
		return (NULL);
	copy_into_str(array, arr_size, str);
	return (str);
}

char	*gc_strarray_asstr(char **array)
{
	size_t	i;
	size_t	arr_size;
	size_t	total_size;
	char	*str;

	if (!array || gc_strarray_size(array) == 0)
		return (gc_strdup(""));
	arr_size = gc_strarray_size(array);
	total_size = 0;
	i = 0;
	while (i < arr_size)
	{
		total_size += gc_strlen(array[i]) + 1;
		i++;
	}
	str = gc_calloc(total_size, sizeof(char));
	if (!str)
		return (NULL);
	copy_into_str(array, arr_size, str);
	return (str);
}

static void	copy_into_str(char **array, size_t arr_size, char *str)
{
	size_t	str_size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < arr_size)
	{
		str_size = gc_strlen(array[i]);
		gc_memmove(&str[j], array[i], str_size);
		j += str_size;
		str[j] = ' ';
		j++;
		i++;
	}
	str[j - 1] = 0;
}
