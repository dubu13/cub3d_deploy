/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:31 by dhasan            #+#    #+#             */
/*   Updated: 2025/08/29 12:12:33 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <emscripten/emscripten.h>

static t_cub *g_cub = NULL;
float sin_table[TRIG_TABLE_SIZE];
float cos_table[TRIG_TABLE_SIZE];

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

void init_trig_tables(void) {
	for (int i = 0; i < TRIG_TABLE_SIZE; ++i) {
		float angle = (float)i * 2.0f * M_PI / (float)TRIG_TABLE_SIZE;
		sin_table[i] = sinf(angle);
		cos_table[i] = cosf(angle);
	}
}

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	init_trig_tables();

	if (!check_extension("maps/map.cub") || !read_file("maps/map.cub", &data))
		return (free_data(&data), 1);

	//wasm opt cache tex.
	data.no_tex_ptr = mlx_load_png(data.no_texture);
	if(!data.no_tex_ptr)
		error("load png failed");
	data.so_tex_ptr = mlx_load_png(data.so_texture);
	if(!data.so_tex_ptr)
		error("load png failed");
	data.we_tex_ptr = mlx_load_png(data.we_texture);
	if(!data.we_tex_ptr)
		error("load png failed");
	data.ea_tex_ptr = mlx_load_png(data.ea_texture);
	if(!data.ea_tex_ptr)
		error("load png failed");
	
	if (!init_game(&data))
		return (error("Initialization failed."), free_data(&data), 1);
	return (0);
}
