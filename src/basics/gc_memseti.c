/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memseti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:04:27 by                   #+#    #+#             */
/*   Updated: 2022/01/22 17:04:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*gc_memseti(void *b, int c, size_t len)
{
	size_t	i;
	int		*bcpy;

	bcpy = b;
	i = 0;
	while (i < len)
	{
		bcpy[i] = c;
		i++;
	}
	return (b);
}
