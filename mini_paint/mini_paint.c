/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:14 by melperri          #+#    #+#             */
/*   Updated: 2022/02/02 05:05:39 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ARG_ERROR "Error: argument\n"
#define OP_ERROR "Error: Operation file corrupted\n"

static int	close_it(FILE *stream)
{
	fclose(stream);
	write(1, OP_ERROR, sizeof(OP_ERROR) - 1);
	return (1);
}
int	main(int ac, char **av)
{
	float		Xa;
	float		Ya;
	float		radius;
	float		Xcenter;
	float		Ycenter;
	int		max_width;
	int		max_height;
	int		ret;
	FILE	*stream;
	char	r;
	char	c;

	if (ac != 2)
	{
		write(1, ARG_ERROR, sizeof(ARG_ERROR) - 1);
		return (1);
	}
	stream = fopen(av[1], "r");
	if (!stream)
	{
		write(1, OP_ERROR, sizeof(OP_ERROR) - 1);
		return (1);
	}
	if ((ret = fscanf(stream, " %d %d %c", &max_width, &max_height, &c)) != 3)
		return (close_it(stream));
	if (max_width < 1 || max_width > 300 || max_height < 1 || max_height > 300)
		return (close_it(stream));

	char	map[max_height][max_width];

	memset(map, c, sizeof(map));
	while ((ret = fscanf(stream, " %c %f %f %f %c", &r, &Xcenter, &Ycenter, &radius, &c)) == 5)
	{
		if (r != 'c' && r != 'C')
			return (close_it(stream));
		if (radius <= 0)
			return (close_it(stream));
		for (int i = 0; i < max_height; i++) {
			for (int j = 0; j < max_width; j++) {
				Xa =  (float)j;
				Ya =  (float)i;
				if (r == 'C') {
					if (sqrtf((Xa - Xcenter) * (Xa - Xcenter) + (Ya - Ycenter) * (Ya - Ycenter)) <= radius)
						map[i][j] = c;
				} else if (r == 'c') {
					if ((sqrtf((Xa - Xcenter) * (Xa - Xcenter) + (Ya - Ycenter) * (Ya - Ycenter)) - radius > -1)
						&& (sqrtf((Xa - Xcenter) * (Xa - Xcenter) + (Ya - Ycenter) * (Ya - Ycenter)) - radius < 1)) {
						if (sqrtf((Xa - Xcenter) * (Xa - Xcenter) + (Ya - Ycenter) * (Ya - Ycenter)) <= radius)
							map[i][j] = c;
					}
				}
			}
		}
	}
	if (ret != EOF)
		return (close_it(stream));
	for (int i = 0; i < max_height; i++) {
		for (int j = 0; j < max_width; j++) {
			write(1, &map[i][j], 1);
		}
		write(1, "\n", 1);
	}
	
	return (0);
}
