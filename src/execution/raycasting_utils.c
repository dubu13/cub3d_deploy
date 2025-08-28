/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:35:03 by dkremer           #+#    #+#             */
/*   Updated: 2024/10/06 12:22:38 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dir_check(float angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	is_direction_positive(float angle, char axis)
{
	if (axis == 'x')
		return (angle > 0 && angle < M_PI);
	if (axis == 'y')
		return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
	return (0);
}

void	set_steps(float angle, float *x_step, float *y_step, char axis)
{
	if (axis == 'x')
	{
		*x_step = TILE_SIZE / tan(angle);
		*y_step = TILE_SIZE;
	}
	else
	{
		*x_step = TILE_SIZE;
		*y_step = TILE_SIZE * tan(angle);
	}
}

void	set_step_direction(float angle, float *x_step, float *y_step, char axis)
{
	if (axis == 'x')
	{
		if ((dir_check(angle, 'y') && *x_step > 0) || (!dir_check(angle, 'y')
				&& *x_step < 0))
			*x_step *= -1;
	}
	else
	{
		if ((dir_check(angle, 'x') && *y_step < 0) || (!dir_check(angle, 'x')
				&& *y_step > 0))
			*y_step *= -1;
	}
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (dir_check(angle, 'x'))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	}
	else
	{
		if (!(dir_check(angle, 'y')))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	}
	*step *= -1;
	return (1);
}
