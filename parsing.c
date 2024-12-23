/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:16:32 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/23 17:50:27 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_map_form(t_parse *parse)
{
	int		i;
	size_t	line;

	line = ft_strlen(parse->map[0]);
	i = 1;
	if (!parse->map || !parse->map[0])
		ft_error("Error\nmap does not exist", parse);
	while (parse->map[i])
	{
		if (ft_strlen(parse->map[i]) != line)
			ft_error("Error\ninvalid map size", parse);
		i++;
	}
	return (1);
}

void	stock_map(char *filename, t_parse *parse)
{
	char	*ligne;
	int		fd;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	parse->count = ft_count_lines(filename, parse);
	parse->map = malloc(sizeof(char *) * (parse->count + 1));
	if (!parse->map)
		exit(EXIT_FAILURE);
	ligne = get_next_line(fd);
	if (!ligne)
	{
		ft_printf("Error\nfile is empty");
		exit(EXIT_FAILURE);
	}
	while (ligne)
	{
		if (ligne[ft_strlen(ligne) - 1] == '\n')
			ligne[ft_strlen(ligne) - 1] = '\0';
		parse->map[i++] = ft_strdup(ligne);
		free(ligne);
		ligne = get_next_line(fd);
	}
	parse->map[i] = NULL;
	close (fd);
}

int	check_file(char *map, t_parse *parse)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error("Error\ncannot open this file", parse);
	close (fd);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	main(int argc, char **argv)
{
	t_parse	parse;
	t_game	game;

	init_parse(&parse);
	if (argc != 2)
		ft_error("Error\nargument error", &parse);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 20) != 0)
		ft_error("Error\nchoose a .ber file", &parse);
	check_file(argv[1], &parse);
	stock_map(argv[1], &parse);
	parsing(&parse, &game);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
