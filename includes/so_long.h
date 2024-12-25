/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:54:31 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/25 17:49:02 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/header/libft.h"
# include "../libft/header/get_next_line.h"
# include "../libft/header/ft_printf.h"
# include <mlx.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_parse
{
	char	**map;
	char	**copy;
	int		line_map;
	int		colonne_map;
	char	*ligne_gnl;
	int		pos;
	int		item;
	int		eexit;
	size_t	long_line;
	int		count;
	int		cols;
	int		rows;
	int		start_x;
	int		start_y;
	int		i;
	int		j;
	int		collectibles;
	char	*ligne;
	int		fd;
}	t_parse;

typedef struct s_game
{
	void	*mlx;
	void	*w;
	int		height;
	int		width;
	char	**map;
	void	*background;
	void	*wall;
	void	*player;
	void	*collec;
	void	*exit;
	int		player_x;
	int		player_y;
	int		total_collectibles;
	int		collected;
	t_parse	*parse;
	int		count;
	int		newx;
	int		newy;
}	t_game;

int		check_map_form(t_parse *parse);
void	stock_map(char *filename, t_parse *parse);
int		check_file(char *map, t_parse *parse);
void	free_map(char **map);
int		check_walls(t_parse *parse);
int		check_items(t_parse *parse);
void	ft_error(char *str, t_parse *parse);
void	init_parse(t_parse *parse);
int		ft_count_lines(char	*filename, t_parse *parse);
void	flood_fill(char	**map, int x, int y, t_parse *parse);
int		find_pos(t_parse *parse);
char	**copy_map(t_parse *parse);
void	print_map(char **map);
void	check_flood(t_parse *parse);
void	parsing(t_parse	*parse, t_game *game);
void	load_textures(t_game *game);
void	init_game(t_game *game, char **map);
void	draw_map(t_game *game, t_parse *parse);
int		key_handler(int keycode, void *param);
int		exit_game(t_game *game, int flag);
void	move_player(t_game *game, t_parse *parse, int newx, int newy);
void	init_game_xpm(t_game *game);
#endif