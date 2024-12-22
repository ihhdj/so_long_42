/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:39:07 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/22 18:35:28 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_x_y(t_parse *parse)
{
	if (parse->map[parse->i][parse->j + 1] == 'C'
		|| parse->map[parse->i][parse->j - 1] == 'C'
		|| parse->map[parse->i + 1][parse->j] == 'C'
		|| parse->map[parse->i - 1][parse->j] == 'C')
		ft_error("Error:\nThe map is not valid", parse);
	return (0);
}

void	move_player(t_game *game, t_parse *parse, int newx, int newy)
{
	printf("Move: %d\n", game->count);
	if (parse->map[newy][newx] == '1')
		return ;
	if (parse->map[newy][newx] == 'C')
	{
		parse->map[newy][newx] = '0';
		game->collected++;
	}
	if (parse->map[newy][newx] == 'E')
	{
		if (game->collected == game->total_collectibles)
			exit_game(game);
		return ;
	}
	parse->map[game->player_y][game->player_x] = '0';
	parse->map[newy][newx] = 'P';
	game->player_x = newx;
	game->player_y = newy;
	draw_map(game, parse);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->w);
	exit(EXIT_SUCCESS);
	return (0);
}
