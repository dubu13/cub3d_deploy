/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:22:36 by dkremer           #+#    #+#             */
/*   Updated: 2025/08/28 19:53:29 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *game, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
}

void	draw_floor_ceiling(t_cub *game, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	if (i > SCREEN_HEIGHT)
		i = SCREEN_HEIGHT;
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, game->data->floor_c);
	i = 0;
	if (t_pix < 0)
		t_pix = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, game->data->ceiling_c);
}

void	draw_wall_segment(t_cub *game, int ray, t_wall *wall)
{
	double		step;
	double		texture_pos;
	int			tex_y;
	uint32_t	color;
	int			y_start;

	step = (double)wall->texture->height / (double)(wall->b_pix - wall->t_pix);
	texture_pos = 0;
	y_start = wall->t_pix;
	while (y_start < wall->b_pix)
	{
		tex_y = (int)texture_pos & (wall->texture->height - 1);
		color = get_texture_color(wall->texture, wall->texture_x, tex_y);
		my_mlx_pixel_put(game, ray, y_start, color);
		texture_pos += step;
		y_start++;
	}
}

void	draw_wall(t_cub *game, int ray, int t_pix, int b_pix)
{
	t_wall	wall_data;

	ft_bzero(&wall_data, sizeof(t_wall));
	wall_data.texture = get_textures(game, game->ray->wall_hit);
	wall_data.texture_x = get_texture_x(game, wall_data.texture);
	wall_data.t_pix = t_pix;
	wall_data.b_pix = b_pix;
	draw_wall_segment(game, ray, &wall_data);
	// mlx_delete_texture(wall_data.texture); // for cache tex.
}

void	render_wall(t_cub *game, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray->distance *= cos(nor_angle(game->ray->angle\
		- game->player->angle));
	wall_h = (TILE_SIZE / game->ray->distance) * (((double)SCREEN_WIDTH / 2) \
		/ tan(game->player->fov / 2));
	if (game->ray->distance == 0)
		wall_h = TILE_SIZE * (((double)SCREEN_WIDTH / 2) \
			/ tan(game->player->fov / 2));
	b_pix = ((double)SCREEN_HEIGHT / 2) + (wall_h / 2);
	t_pix = ((double)SCREEN_HEIGHT / 2) - (wall_h / 2);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
	draw_wall(game, ray, t_pix, b_pix);
}
