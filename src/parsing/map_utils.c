/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:15:05 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/08 17:59:09 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_position(t_data *data, unsigned int x, unsigned int y)
{
	if (data->pos_x != -1 || data->pos_y != -1)
		return (error("Multiple player positions."), 0);
	data->pos_x = x;
	data->pos_y = y;
	data->dir = data->map[y][x];
	return (1);
}

int	check_nl(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (error("Invalid map/map info."), 0);
		i++;
	}
	return (1);
}

int	file_to_map(int fd, t_data *data, char *line)
{
	if (!line)
		return (error("Missing map."), 0);
	while (line)
	{
		data->map_temp = ft_strjoin_gnl(data->map_temp, line);
		free(line);
		if (!data->map_temp)
			return (error("Memory allocation failed."), 0);
		data->height++;
		line = get_next_line(fd);
	}
	free(line);
	if (!check_nl(data->map_temp))
		return (free(data->map_temp), 0);
	data->map = ft_split(data->map_temp, '\n');
	free(data->map_temp);
	data->map_temp = NULL;
	if (!data->map)
		return (error("Memory allocation failed."), 0);
	return (1);
}
