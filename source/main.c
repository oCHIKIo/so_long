/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:12 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/29 20:31:06 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5 || filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r'
		|| filename[len - 5] == '/')
	{
		ft_putstr_fd("\033[1;31mError: File (must be .ber with a name)\033[0m\n",
			2);
		return (0);
	}
	return (1);
}

static void	init_game(t_game *game)
{
	game->mlx = 0;
	game->win = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->width = 0;
	game->height = 0;
	game->moves = 0;
	game->last_dx = 0;
	game->last_dy = 1;
}

static void	setup_game(t_game *game, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("\033[1;31mError: Invalid number of arguments\033[0m\n",
			2);
		exit(1);
	}
	if (!check_file_extension(av[1]))
		exit(1);
	game->map = read_map(av[1]);
	if (!check_map_validity(game))
	{
		free(game->map);
		exit(1);
	}
}

static void	cleanup_game(t_game *game)
{
	destroy_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map);
}

int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game);
	setup_game(&game, ac, av);
	ft_putstr_fd("\033[1;36mGame Launched Successfully\033[0m\n", 1);
	init_graphics(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L, key_press, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
