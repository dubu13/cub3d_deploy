/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:45:31 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/08 18:35:59 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	convert_rgb(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

char	*skip_nl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

bool	is_texture(char *contect)
{
	if (!ft_strncmp(contect, "NO ", 3))
		return (true);
	if (!ft_strncmp(contect, "SO ", 3))
		return (true);
	if (!ft_strncmp(contect, "WE ", 3))
		return (true);
	if (!ft_strncmp(contect, "EA ", 3))
		return (true);
	return (false);
}

bool	is_color(char *contect)
{
	if (!ft_strncmp(contect, "F ", 2))
		return (true);
	if (!ft_strncmp(contect, "C ", 2))
		return (true);
	return (false);
}

int	save_texture(t_data *data, char *texture, char *path)
{
	if (!ft_strncmp(texture, "NO", 3))
	{
		if (data->no_texture)
			return (0);
		data->no_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(texture, "SO", 3))
	{
		if (data->so_texture)
			return (0);
		data->so_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(texture, "WE", 3))
	{
		if (data->we_texture)
			return (0);
		data->we_texture = ft_strdup(path);
	}
	else if (!ft_strncmp(texture, "EA", 3))
	{
		if (data->ea_texture)
			return (0);
		data->ea_texture = ft_strdup(path);
	}
	return (1);
}
