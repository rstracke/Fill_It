/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readbuf_sym_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:54:06 by rstracke          #+#    #+#             */
/*   Updated: 2019/02/05 18:54:21 by rstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			readbuf_sym_valid(char *buf, int size_buf, t_prm prm)
{
	int		count_lb;
	int		count_hash;

	count_lb = 0;
	count_hash = 0;
	prm.pos = 0;
	while (buf[prm.pos] && prm.pos < BUFF_SIZE - 1)
	{
		if (buf[prm.pos] != '#' && buf[prm.pos] != '.' && buf[prm.pos] != '\n')
			return (0);
		if (buf[prm.pos] == '\n' && (prm.pos - count_lb * 5) != 4)
			return (0);
		if (((buf[prm.pos] == '\n') ? ++count_lb : count_lb) > 4)
			return (0);
		if (((buf[prm.pos] == '#') ? ++count_hash : count_hash) > TETRIMINO_SIZE)
			return (0);
			prm.pos++;
	}
	return ((count_hash == TETRIMINO_SIZE && count_lb == 4) ? 1 : 0);
}
