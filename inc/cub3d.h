/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:20 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/09 14:44:14 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include "cub3d_types.h"
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

//raycasting_utils.c
int				inter_check(float angle, float *inter, float *step,
					int is_horizon);
void			set_step_direction(float angle, float *x_step, float *y_step,
					char axis);
void			set_steps(float angle, float *x_step, float *y_step, char axis);
int				is_direction_positive(float angle, char axis);
int				dir_check(float angle, char c);
//raycasting.c
void			raycasting(t_cub *cub);
//paser.c
int				read_file(char *file, t_data *data);
//checker.c
int				check_extension(char *file);
int				check_color(char **rgb);
int				check_texture(char *contect);
int				is_map_enclosed(t_data *data);
int				save_position(t_data *data, unsigned int x, unsigned int y);
int				check_data(t_data *data);
//parser_utils.c
char			*skip_nl(int fd);
bool			is_texture(char *contect);
bool			is_color(char *contect);
int				ft_is_rgb(char *c);
int32_t			convert_rgb(int r, int g, int b, int a);
int	save_texture(t_data *data, char *texture, char *path);
//map_utils.c
int				char_check(t_data *data);
int				file_to_map(int fd, t_data *data, char *line);
//rendering.c
void			render_wall(t_cub *mlx, int ray);
//rendering_utils.c
float			nor_angle(float angle);
double			get_texture_x(t_cub *game, mlx_texture_t *texture);
mlx_texture_t	*get_textures(t_cub *game, int wall_hit);
uint32_t		get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);
//movement
void			hook(t_cub *game, double move_x, double move_y);
void			mlx_key(mlx_key_data_t keydata, void *ml);
//msg_free.c
void			ft_exit(void *param);
void			free_2d_array(char **array);
void			error(char *msg);
void			free_data(t_data *data);
#endif
