/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:42:51 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/01 13:36:59 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_release(mlx_key_data_t keydata, t_cub *game)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->player->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		game->player->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		game->player->rot = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *ml)
{
	t_cub	*game;

	game = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		ft_exit(game);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->l_r = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->l_r = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->u_d = -1;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		game->player->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		game->player->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		game->player->rot = 1;
	ft_release(keydata, game);
}

void	rotate_player(t_cub *game, int i)
{
	if (i == 1)
	{
		game->player->angle += ROTATION_SPEED;
		if (game->player->angle > 2 * M_PI)
			game->player->angle -= 2 * M_PI;
	}
	else
	{
		game->player->angle -= ROTATION_SPEED;
		if (game->player->angle < 0)
			game->player->angle += 2 * M_PI;
	}
}

void	move_player(t_cub *game, double move_x, double move_y)
{
	int	y;
	int	x;
	int	new_x;
	int	new_y;

	new_x = roundf(game->player->p_x + move_x);
	new_y = roundf(game->player->p_y + move_y);
	x = (new_x / TILE_SIZE);
	y = (new_y / TILE_SIZE);
	if (game->data->map[y][x] != '1' &&
		(game->data->map[y][game->player->p_x / TILE_SIZE] != '1' &&
			game->data->map[game->player->p_y / TILE_SIZE][x] != '1'))
	{
		game->player->p_x = new_x;
		game->player->p_y = new_y;
	}
}

void	hook(t_cub *game, double move_x, double move_y)
{
	if (game->player->rot == 1)
		rotate_player(game, 1);
	if (game->player->rot == -1)
		rotate_player(game, 0);
	if (game->player->u_d == 1)
	{
		move_x = cos(game->player->angle) * PLAYER_SPEED;
		move_y = sin(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->u_d == -1)
	{
		move_x = -cos(game->player->angle) * PLAYER_SPEED;
		move_y = -sin(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->l_r == 1)
	{
		move_x = -sin(game->player->angle) * PLAYER_SPEED;
		move_y = cos(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->l_r == -1)
	{
		move_x = sin(game->player->angle) * PLAYER_SPEED;
		move_y = -cos(game->player->angle) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y);
}
