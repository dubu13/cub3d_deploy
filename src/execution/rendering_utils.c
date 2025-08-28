/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:14 by dhasan            #+#    #+#             */
/*   Updated: 2025/08/27 19:02:10 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_textures(t_cub *game, int wall_hit)
{
	char			*texture;
	const double	normalized_angle = nor_angle(game->ray->angle);

	if (wall_hit == 0)
	{
		if (dir_check(normalized_angle, 'y'))
			texture = game->data->we_texture;
		else
			texture = game->data->ea_texture;
	}
	else
	{
		if (dir_check(normalized_angle, 'x'))
			texture = game->data->so_texture;
		else
			texture = game->data->no_texture;
	}
	return (mlx_load_png(texture));
}

double	get_texture_x(t_cub *game, mlx_texture_t *texture)
{
	float	wall_x;

	if (game->ray->wall_hit == 0)
		wall_x = fmodf((double)game->ray->hit_y, (double)TILE_SIZE);
	else
		wall_x = fmodf((double)game->ray->hit_x, (double)TILE_SIZE);
	return (wall_x / (double)TILE_SIZE * (double)texture->width);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	// return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF);
}

float	nor_angle(float angle)
{
	while (angle < 0)
		angle += (2 * M_PI);
	while (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
