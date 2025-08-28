/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:35 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/08 18:31:43 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *contect, t_data *data)
{
	char	**texture;
	char	*path;

	texture = ft_split(contect, ' ');
	if (texture[1])
	{
		path = ft_strtrim(texture[1], " \t\n\r\v\f");
		if (texture[2] || !check_texture(path))
			return (free(path), free_2d_array(texture),
				error("Invalid texture."), 0);
		if (!save_texture(data, texture[0], path))
			return (free(path), free_2d_array(texture),
				error("Multiple textures for one wall."), 0);
		free(path);
		path = NULL;
	}
	free_2d_array(texture);
	return (1);
}

int	parse_color(char *content, t_data *data, char type)
{
	char	**colors;
	int		rgb[3];

	colors = ft_split(content, ',');
	if (!check_color(colors))
		return (free_2d_array(colors), error("Invalid color."), 0);
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	if (type == 'f')
		data->floor_c = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	else
		data->ceiling_c = convert_rgb(rgb[0], rgb[1], rgb[2], 255);
	free_2d_array(colors);
	return (1);
}

int	parse_map(int fd, t_data *data, char *line)
{
	data->pos_x = -1;
	data->pos_y = -1;
	if (!file_to_map(fd, data, line))
		return (0);
	if (!char_check(data) || !is_map_enclosed(data))
		return (0);
	if (data->pos_x == -1 || data->pos_y == -1)
		return (error("Player not found."), 0);
	return (1);
}

int	save_content(char *content, t_data *data, int fd)
{
	while (content)
	{
		if (is_texture(content))
			if (!parse_texture(content, data))
				return (free(content), 0);
		if (*content == 'F')
			if (!parse_color(content + 2, data, 'f'))
				return (free(content), 0);
		if (*content == 'C')
			if (!parse_color(content + 2, data, 'c'))
				return (free(content), 0);
		if (!is_texture(content) && *content != 'F' && *content != 'C')
		{
			if (!parse_map(fd, data, content))
				return (0);
			break ;
		}
		free(content);
		content = skip_nl(fd);
	}
	return (1);
}

int	read_file(char *file, t_data *data)
{
	char	*content;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error("File does not exist or is not readable."), 0);
	content = skip_nl(fd);
	if (!save_content(content, data, fd) || !check_data(data))
		return (close(fd), 0);
	close(fd);
	return (1);
}
