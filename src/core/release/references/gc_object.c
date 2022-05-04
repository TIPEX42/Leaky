/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 14:39:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/release/core.h"

void	gc_object_start(void *ptr)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = gc_get_internal_ptr_index(ptr);
}

void	gc_object_end(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = -1;
}
