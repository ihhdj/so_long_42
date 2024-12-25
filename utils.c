/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:39:07 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/25 17:57:29 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	move_player(t_game *game, t_parse *parse, int newx, int newy)
{
	ft_printf("Move: %d\n", game->count);
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
			exit_game(game, 1);
		return ;
	}
	parse->map[game->player_y][game->player_x] = '0';
	parse->map[newy][newx] = 'P';
	game->player_x = newx;
	game->player_y = newy;
	draw_map(game, parse);
}

int	exit_game(t_game *game, int flag)
{
	if (game->map != NULL)
		free_map(game->parse->map);
	if (game->background)
		mlx_destroy_image(game->mlx, game->background);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collec)
		mlx_destroy_image(game->mlx, game->collec);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	mlx_destroy_window(game->mlx, game->w);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(flag);
}

void	init_game_xpm(t_game *game)
{
	game->background = NULL;
	game->wall = NULL;
	game->player = NULL;
	game->collec = NULL;
	game->exit = NULL;
}
