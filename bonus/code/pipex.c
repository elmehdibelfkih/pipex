/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/14 02:33:56 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	vars.trm = dup(1);
	if (argc != 5)
		exit_message (0, &vars);
	parsing_path(&vars, envp);
	parsing_args(&vars, argv, argc);
	my_fopen(&vars);
	if (my_proccesses(&vars, 0) == -1)
		exit_message(1, &vars);
	ft_clear (vars.path, 10000);
	ft_clear (vars.cmds, 10000);
	free(vars.input);
	free(vars.output);
	return (0);
}
