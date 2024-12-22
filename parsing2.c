/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:42:19 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/22 13:48:17 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_walls(t_parse *p)
{
	int	i;

	i = 0;
	p->line_map = 0;
	while (p->map[p->line_map])
		p->line_map++;
	p->colonne_map = ft_strlen(p->map[0]);
	while (i < p->colonne_map)
	{
		if (p->map[0][i] != '1' || p->map[p->line_map - 1][i] != '1')
			ft_error("Error\nmap is not surrounded by walls", p);
		i++;
	}
	i = 0;
	while (i < p->line_map)
	{
		if (p->map[i][0] != '1' || p->map[i][p->colonne_map - 1] != '1')
			ft_error("Error\nmap is not surrounded by walls", p);
		i++;
	}
	return (1);
}

void	init_parse(t_parse *parse)
{
	parse->map = NULL;
	parse->eexit = 0;
	parse->item = 0;
	parse->pos = 0;
}

int	check_items(t_parse *parse)
{
	parse->i = 0;
	while (parse->map[parse->i])
	{
		parse->j = 0;
		while (parse->map[parse->i][parse->j])
		{
			if (parse->map[parse->i][parse->j] == 'C')
				parse->item += 1;
			else if (parse->map[parse->i][parse->j] == 'P')
				parse->pos += 1;
			else if (parse->map[parse->i][parse->j] == 'E')
			{
				if (parse->map[parse->i][parse->j - 1] == 'C')
					ft_error("Error:\nthe map is not valid", parse);
				parse->eexit += 1;
			}
			else if (parse->map[parse->i][parse->j] != '1' && parse->map[parse->i][parse->j] != '0')
				ft_error("Error:\ninvalid character", parse);
			parse->j++;
		}
		parse->i++;
	}
	if (parse->eexit != 1 || parse->pos != 1 || parse->item <= 0)
		ft_error("Error\ninvalid map", parse);
	return (1);
}

void	ft_error(char *str, t_parse *parse)
{
	ft_printf(str);
	if (parse->map != NULL)
		free_map(parse->map);
	exit(EXIT_FAILURE);
}

int	ft_count_lines(char	*filename, t_parse *parse)
{
	int		fd;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error:\ncannot open this file", parse);
	parse->ligne_gnl = get_next_line(fd);
	while (parse->ligne_gnl)
	{
		count++;
		free (parse->ligne_gnl);
		parse->ligne_gnl = get_next_line(fd);
	}
	close (fd);
	return (count);
}
