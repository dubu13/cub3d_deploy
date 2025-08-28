/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:58:32 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/09 19:26:07 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_check(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	x = 0;
	while (data->map[y])
	{
		x = 0;
		if (data->map[y][0] == '\0' || data->map[y][0] == '\n')
			return (error("Invalid map."), 0);
		while (data->map[y][x])
		{
			if (!ft_strchr(" 01NSEW", data->map[y][x]))
				return (error("Map with invalid char."), 0);
			if (ft_strchr("NSEW", data->map[y][x]))
				if (!save_position(data, x, y))
					return (0);
			x++;
		}
		if (x > data->width)
			data->width = x;
		y++;
	}
	return (1);
}

int	check_around_position(t_data *data, unsigned int x, unsigned int y)
{
	unsigned int	prev_len;

	prev_len = ft_strlen(data->map[y - 1]);
	if (x == 0 || x == data->width - 1 || y == 0 || y == data->height - 1)
		return (0);
	else if (data->map[y - 1][x] == ' ' || data->map[y][x - 1] == ' ' || \
		data->map[y][x + 1] == ' ' || data->map[y + 1][x] == ' ')
		return (0);
	else if (data->map[y - 1][x] == '\0' || data->map[y][x - 1] == '\0' || \
		data->map[y][x + 1] == '\0' || data->map[y + 1][x] == '\0')
		return (0);
	else if (x > prev_len)
		return (0);
	return (1);
}

int	is_map_enclosed(t_data *data)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][0] == '\n' )
				return (error("Newline inside map."), 0);
			if (data->map[y][x] != '1' && data->map[y][x] != ' ')
				if (!check_around_position(data, x, y))
					return (error("Map is not enclosed by walls."), 0);
			x++;
		}
		y++;
	}
	return (1);
}
