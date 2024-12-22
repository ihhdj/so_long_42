/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:37 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/22 13:41:21 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void parsing(t_parse *parse, t_game *game)
{
	check_map_form(parse);
	check_walls(parse);
	check_items(parse);
	find_pos(parse);

	parse->copy = copy_map(parse);
	flood_fill(parse->copy, parse->start_x, parse->start_y, parse);
	check_flood(parse);
	init_game(game, parse->copy);
	load_textures(game);
	draw_map(game, parse);
	game->player_x = parse->start_x;
	game->player_y = parse->start_y;
	game->total_collectibles = parse->item;
	game->collected = 0;
	game->parse = parse;
	mlx_hook(game->window, 2, 1L << 0, key_handler, game);
	mlx_hook(game->window, 17, 0, exit_game, game);
	mlx_loop(game->mlx);
	free_map(parse->copy);
	free_map(parse->map);
}



void	init_game(t_game *game, char **map)
{
	game->count = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->map = map;
	game->height = 0;
	while (map[game->height])
		game->height++;
	game->width = ft_strlen(map[0]);
	game->window = mlx_new_window(game->mlx, game->width * 64,
			game->height * 64, "So_long");
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->background = mlx_xpm_file_to_image(game->mlx, "xpm/grass.xpm", &width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, "xpm/trees.xpm", &width, &height);
	game->player = mlx_xpm_file_to_image(game->mlx, "xpm/chill.xpm", &width, &height);
	game->collec = mlx_xpm_file_to_image(game->mlx, "xpm/gold.xpm", &width, &height);
	game->exit = mlx_xpm_file_to_image(game->mlx, "xpm/exit.xpm", &width, &height);
	if (!game->background || !game->wall || !game->player || !game->collec || !game->exit)
	{
		ft_printf("Error:\nxpm file is not available");
		exit(EXIT_FAILURE);
	}
}
void	draw_map(t_game *game,t_parse *parse)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->window, game->background,x * 64, y * 64);
			if (parse->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->window, game->wall,x * 64, y * 64);
			if (parse->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->window, game->player,x * 64, y * 64);
			if (parse->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->window, game->exit,x * 64, y * 64);
			if (parse->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->window, game->collec,x * 64 ,y * 64);
			x++;
		}
		y++;
	}
}
int key_handler(int keycode, void *param)
{
	t_game *game;
	t_parse *parse;
	
	game = (t_game *)param;
	parse = game->parse;
	game->newx = game->player_x;
	game->newy = game->player_y;
	if (keycode == KEY_W)
		game->newy--;
	else if (keycode == KEY_S)
		game->newy++;
	else if (keycode == KEY_A)
		game->newx--;
	else if (keycode == KEY_D)
		game->newx++;
	else if (keycode == KEY_ESC)
		exit_game(game);
	if (parse->map[game->newy][game->newx] == '1')
		return (0);
	else
		game->count++;
	move_player(game, parse, game->newx, game->newy);
	return (0);
}


int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit(EXIT_SUCCESS);
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
