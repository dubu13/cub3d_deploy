/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2025/08/27 19:18:47 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <emscripten/emscripten.h>

static t_cub *g_cub = NULL;

void	init_player(t_cub *cub)
{
	cub->player->p_x = cub->data->pos_x * TILE_SIZE + TILE_SIZE / 2;
	cub->player->p_y = cub->data->pos_y * TILE_SIZE + TILE_SIZE / 2;
	cub->player->fov = (FOV * M_PI / 180);
	if (cub->data->dir == 'N')
		cub->player->angle = NORTH;
	else if (cub->data->dir == 'S')
		cub->player->angle = SOUTH;
	else if (cub->data->dir == 'E')
		cub->player->angle = EAST;
	else if (cub->data->dir == 'W')
		cub->player->angle = WEST;
}

void	game_loop(void *param)
{
    t_cub	*cub = param;

    if (!cub->img) {
        cub->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!cub->img) return;
        if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0) {
            mlx_delete_image(cub->mlx, cub->img);
            cub->img = NULL;
            return;
        }
    }

    // Clear the image (optional: fill with green for debug)
    // for (int y = 0; y < (int)cub->img->height; ++y)
    //     for (int x = 0; x < (int)cub->img->width; ++x)
    //         mlx_put_pixel(cub->img, x, y, 0x00FF00FF); // RGBA, alpha=0xFF

    // Now run your game logic
    hook(cub, 0, 0);
    raycasting(cub);
}

void emscripten_main_loop(void) {
	if (g_cub && g_cub->mlx)
		mlx_loop(g_cub->mlx);
}

int	init_game(t_data *data)
{
	static t_cub		cub;
	static t_player	player;
	static t_ray		ray;

	ft_bzero(&cub, sizeof(t_cub));
	ft_bzero(&player, sizeof(t_player));
	ft_bzero(&ray, sizeof(t_ray));
	
	cub.data = data;
	cub.player = &player;
	cub.ray = &ray;
	
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (!cub.mlx)
		return (0);
		
	init_player(&cub);
	mlx_close_hook(cub.mlx, &ft_exit, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_key_hook(cub.mlx, &mlx_key, &cub);
	
	g_cub = &cub;
	emscripten_set_main_loop(emscripten_main_loop, 0, true);
	
	// mlx_loop(cub.mlx);
	// mlx_terminate(cub.mlx);
	// ft_exit(&cub);
	return (1);
}


int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));

	if (!check_extension("maps/valid/map.cub") || !read_file("maps/valid/map.cub", &data))
		return (free_data(&data), 1);
	if (!init_game(&data))
		return (error("Initialization failed."), free_data(&data), 1);
	return (0);
}
