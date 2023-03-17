/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/17 01:31:58 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		i;

	if (argc < 5)
		exit_message (0, &vars);
	if (!*envp)
		exit_message (9, &vars);
	i = 1;
	parsing_path(&vars, envp);
	here_doc(&vars, argv, argc);
	my_fopen(&vars);
	while (i < vars.i)
	{
		if (bonus_proccesses(&vars, i) == -1)
			exit_message(1, &vars);
		i += 2;
	}
	proccess3(&vars);
	if (vars.here_doc_status == 1)
		unlink("here_doc");
	return (ft_clear (vars.cmds, 10000), ft_clear (vars.path, 10000),
		free(vars.output), free(vars.input), 0);
}
