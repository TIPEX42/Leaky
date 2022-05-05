/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:54:10 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:34:54 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cored.h"
#include "leaky.h"

int	gc_has_global_parent(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->current_parent == -1)
		return (LK_FALSE);
	return (LK_TRUE);
}

t_ptr	*gc_ptr(int64_t index)
{
	t_gc	*allocator;

	if (index == -1)
		return (NULL);
	allocator = gc_get();
	return (&allocator->pointers[index]);
}

int	gc_is_valid_ptr_index(int64_t index)
{
	if (index >= 0)
		return (1);
	return (0);
}

size_t	gc_child_count(int64_t ptr)
{
	t_gc	*allocator;

	if (!gc_is_valid_ptr_index(ptr))
		return (0);
	allocator = gc_get();
	return (allocator->pointers[ptr].child_count);
}

size_t	gc_parent_count(int64_t ptr)
{
	t_gc	*allocator;

	if (!gc_is_valid_ptr_index(ptr))
		return (0);
	allocator = gc_get();
	return (allocator->pointers[ptr].parent_count);
}
