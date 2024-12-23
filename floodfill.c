/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:39:00 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/23 16:35:58 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	flood_fill(char	**map, int x, int y, t_parse *p)
{
	if (x < 0 || y < 0 || y >= p->count || x >= p->colonne_map
		|| ft_strchr("1VE", map[y][x]))
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, p);
	flood_fill(map, x - 1, y, p);
	flood_fill(map, x, y + 1, p);
	flood_fill(map, x, y - 1, p);
}

int	find_pos(t_parse *parse)
{
	int	y;
	int	x;

	parse->start_x = -1;
	parse->start_y = -1;
	y = 0;
	while (y < parse->count)
	{
		x = 0;
		while (x < parse->colonne_map)
		{
			if (parse->map[y][x] == 'P')
			{
				parse->start_x = x;
				parse->start_y = y;
				return (1) ;
			}
			x++;
		}
		y++;
	}
	if (parse->start_x == -1 || parse->start_y == -1)
	ft_error("Error:\nno starting point found", parse);
	return (0);
}

char	**copy_map(t_parse *parse)
{
	char	**map_cpy;
	int		i;

	i = 0;
	map_cpy = malloc(sizeof(char *) * (parse->count + 1));
	while (i < parse->count)
	{
		map_cpy[i] = ft_strdup(parse->map[i]);
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

void	print_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_printf(map[i]);
		write(1, "\n", 2);
		i++;
	}
	write(1, "\n", 2);
}

void	check_flood(t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	if (p->collectibles > 0)
		ft_error("Error:\nthe map is not valid", p);
	while (i < p->count)
	{
		j = 0;
		while (j < p->colonne_map)
		{
			if (p->copy[i][j] == 'C')
				ft_error("Error:\nplayer cannot reach all collectibles", p);
			if (p->copy[i][j] == 'E')
				if (p->copy[i + 1][j] != 'V' && p->copy[i - 1][j] != 'V'
					&& p->copy[i][j + 1] != 'V'
					&& p->copy[i][j - 1] != 'V')
					ft_error("Error:\nplayer cannot reach the exit", p);
			j++;
		}
		i++;
	}
}
