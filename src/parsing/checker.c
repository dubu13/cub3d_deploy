/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:55:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/10/08 18:02:47 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strncmp(extension, ".cub\0", 5) != 0)
		return (error("Map should be in '.cub' format."), 0);
	return (1);
}

int	check_texture(char *contect)
{
	int	fd;

	fd = open(contect, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_color(char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[2][0] == '\n')
		return (0);
	if (!ft_is_rgb(rgb[0]) || !ft_is_rgb(rgb[1]) || !ft_is_rgb(rgb[2]))
		return (0);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		return (0);
	return (1);
}

int	check_data(t_data *data)
{
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture || !data->floor_c || !data->ceiling_c
		|| !data->map)
		return (error("Missing info in file."), 0);
	return (1);
}

int	ft_is_rgb(char *c)
{
	int	invalid_char;

	invalid_char = 0;
	while (*c)
	{
		if (!(*c >= '0' && *c <= '9') && *c != '\n')
			invalid_char = 1;
		c++;
	}
	if (invalid_char)
		return (0);
	return (1);
}
