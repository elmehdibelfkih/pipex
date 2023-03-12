/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/12 05:52:25 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		i;

	if (argc <= 3)
		exit_message (0, &vars);
	i = 0;
	parsing_path(&vars, envp);
	parsing_args(&vars, argv, argc);
	vars.fd_in = open(vars.input, O_RDWR, 0777);
	vars.fd_out = open(vars.output, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (vars.fd_out == -1 || vars.fd_in == -1)
		exit_message (0, &vars);
	dup2(vars.fd_in, 0);
	dup2(vars.fd_out, 1);
	close(vars.fd_in);
	close(vars.fd_out);
	my_proccesses(&vars, i);
	return (0);
}
