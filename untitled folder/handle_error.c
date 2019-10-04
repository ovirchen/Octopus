/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:44:30 by abodnar           #+#    #+#             */
/*   Updated: 2019/05/01 17:44:31 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	handle_error(t_doom *params)
{
	int i;

	ft_printf("%s\n", params->error);
	ft_strdel(&params->error);
	if (params->did_read_map)
	{
		i = -1;
		while (++i < params->map_height)
			ft_strdel((char**)&params->map[i]);
		ft_strdel((char**)&params->map);
	}
	return (1);
}
