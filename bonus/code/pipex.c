/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/14 09:09:15 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		i;

	if (argc < 5)
		exit_message (0, &vars);
	i = 1;
	vars.trm = dup(1);
	parsing_path(&vars, envp);
	parsing_args(&vars, argv, argc);
	my_fopen(&vars);
	while (i < vars.i)
	{
		if (my_proccesses(&vars, i) == -1)
			exit_message(1, &vars);
		i += 2;
	}
	proccess3(&vars);
	return (ft_clear (vars.cmds, 10000), ft_clear (vars.path, 10000),
		free(vars.output), free(vars.input), 0);
}
