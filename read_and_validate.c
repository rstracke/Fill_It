/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:19:35 by ggrimes           #+#    #+#             */
/*   Updated: 2019/02/05 19:02:13 by rstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			**read_and_validate(int fd, t_prm *prm)
{
	int		ret;
	char	*readbuf;
	int		**tets;
	int		*tet;

	tets = NULL;
	readbuf = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, readbuf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (NULL);
		readbuf[ret] = '\0';
		(*prm).size_of_last_tet = ret;
		CHECK(readbuf_size_valid(readbuf, ret));
		CHECK(readbuf_sym_valid(readbuf, *prm));
		CHECK((tet = get_tet(readbuf, *prm)));
		CHECK(tet_is_valid(tet));
		CHECK(!(++(*prm).cnt_tets > 26));
		CHECK((tets = add_tet(&tets, (*prm).cnt_tets, tet)));
	}
	if ((*prm).size_of_last_tet != 20)
		return (NULL);
	ft_strdel(&readbuf);
	return (tets);
}

int			readbuf_size_valid(char *buf, int size_buf)
{
	if (size_buf == BUFF_SIZE && buf[size_buf - 1] == '\n'
			&& buf[size_buf - 2] == '\n')
		return (1);
	if (size_buf == BUFF_SIZE - 1 && buf[size_buf - 1] == '\n')
		return (1);
	return (0);
}

int            readbuf_sym_valid(char *buf, t_prm prm)
{
    int        count_lb;
    int        count_hash;
    
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

void		put_null_points(int x, int y, t_prm *prm)
{
	(*prm).x0 = x;
	(*prm).y0 = y;
}

int			tet_is_valid(int *tet)
{
	int		count_comm;
	int		i;
	int		j;

	count_comm = 0;
	i = -1;
	while ((i += 2) <= TETRIMINO_SIZE * 2 - 2)
	{
		j = i;
		while ((j += 2) <= TETRIMINO_SIZE * 2)
		{
			if (tet[i] + 1 == tet[j] && tet[i + 1] == tet[j + 1])
				count_comm++;
			if (tet[i] == tet[j] && tet[i + 1] + 1 == tet[j + 1])
				count_comm++;
		}
	}
	if (count_comm == 3 || count_comm == 4)
		return (1);
	return (0);
}
