/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:07:48 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/07 18:11:50 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(float x, float y, t_cub *game)
{
	unsigned int	x_m;
	unsigned int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= game->data->height || x_m >= game->data->width))
		return (0);
	if (game->data->map[y_m] && x_m <= strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_cub *game, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	set_steps(angle, &x_step, &y_step, 'x');
	h_y = floor((double)game->player->p_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player->p_x + (h_y - game->player->p_y) / tan(angle);
	set_step_direction(angle, &x_step, &y_step, 'x');
	while (wall_hit(h_x, h_y - pixel, game))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray->hit_x = h_x;
	return (sqrt(pow(h_x - game->player->p_x, 2) + pow(h_y - game->player->p_y,
				2)));
}

float	get_v_inter(t_cub *game, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	set_steps(angle, &x_step, &y_step, 'y');
	v_x = floor((double)game->player->p_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = game->player->p_y + (v_x - game->player->p_x) * tan(angle);
	set_step_direction(angle, &x_step, &y_step, 'y');
	while (wall_hit(v_x - pixel, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray->hit_y = v_y;
	return (sqrt(pow(v_x - game->player->p_x, 2) + pow(v_y - game->player->p_y,
				2)));
}

void	raycasting(t_cub *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray->angle = game->player->angle - (game->player->fov / 2);
	while (ray < SCREEN_WIDTH)
	{
		game->ray->wall_hit = 0;
		v_inter = get_v_inter(game, nor_angle(game->ray->angle));
		h_inter = get_h_inter(game, nor_angle(game->ray->angle));
		if (v_inter <= h_inter)
		{
			game->ray->distance = v_inter;
		}
		else
		{
			game->ray->distance = h_inter;
			game->ray->wall_hit = 1;
		}
		render_wall(game, ray);
		ray++;
		game->ray->angle += (game->player->fov / SCREEN_WIDTH);
	}
}
