/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:28:05 by melperri          #+#    #+#             */
/*   Updated: 2022/02/02 05:09:06 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ARG_ERROR "Error: argument\n"
#define OP_ERROR "Error: Operation file corrupted\n"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int	ft_close(FILE *stream)
{
	write(1, OP_ERROR, sizeof(OP_ERROR) - 1);
	fclose(stream);
	return (1);
}

int	main(int ac, char **av)
{
	float	Xa;
	float	Ya;
	float	width;
	float	height;
	float	Xend;
	float	Yend;
	float	Xstart;
	float	Ystart;
	int		ret;
	int		map_width;
	int		map_height;
	char	r;
	char	c;

	FILE	*stream;

	if (ac != 2) {
		write(1, ARG_ERROR, sizeof(ARG_ERROR) - 1);
		return (1);
	} else {
		stream = fopen(av[1], "r");
		if (!stream)
		{
			write(1, OP_ERROR, sizeof(OP_ERROR) - 1);
			return (1);
		}
		if ((ret = fscanf(stream, " %d %d %c", &map_width, &map_height, &c)) != 3)
			return (ft_close(stream));
		if (map_width < 1 || map_width > 300 || map_height < 1 || map_height > 300)
			return (ft_close(stream));

		char	map[map_height][map_width];

		memset(map, c, sizeof(map));
		while ((ret = fscanf(stream, " %c %f %f %f %f %c", &r, &Xstart, &Ystart, &width, &height, &c)) == 6) {
			if (r != 'r' && r != 'R')
				return (ft_close(stream));
			if (width < 0 || height < 0)
				return (ft_close(stream));
			Xend = Xstart + width;
			Yend = Ystart + height;
			for (int i = 0; i < map_height; i++) {
				for (int j = 0; j < map_width; j++) {
					Xa = (float)j;
					Ya = (float)i;
					if (r == 'R') {
						if (Xa >= Xstart && Xa <= Xend && Ya >= Ystart && Ya <= Yend)
							map[i][j] = c;
					} else if (r == 'r') {
						if (((Xa - Xend > -1) && (Xa - Xend < 1)) || ((Xa - Xstart > -1) && (Xa - Xstart < 1))
							|| ((Ya - Yend > -1) && (Ya - Yend < 1)) || ((Ya - Ystart > -1) && (Ya - Ystart < 1))) {
							if (Xa >= Xstart && Xa <= Xend && Ya >= Ystart && Ya <= Yend)
								map[i][j] = c;
						}
					}
				}
			}
		}
		if (ret != EOF)
			return (ft_close(stream));
		for (int i = 0; i < map_height; i++) {
			for (int j = 0; j < map_width; j++) {
				write(1, &map[i][j], 1);
			}
			write(1, "\n", 1);
		}
	}
	return (0);
}
