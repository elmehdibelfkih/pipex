/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:58:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/13 06:46:38 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	exit_message(int i, t_vars *vars)
{
	char	**message;

	(void)vars;
	message = malloc(9 * sizeof(char *));
	message[0] = ft_strdup("invalid input !");
	message[1] = ft_strdup("fork error !");
	message[2] = ft_strdup("pipe error !!");
	message[3] = ft_strdup(" command not found !!");
	message[4] = ft_strdup(" execve error !!");
	message[5] = ft_strdup("There is no input file !!");
	message[6] = NULL;
	write (vars->trm, message[i], strlen(message[i]));
	if (i == 1 || i == 2 || i == 3 || i == 4)
	{
		ft_clear (vars->path, 10000);
		ft_clear (vars->cmds, 10000);
		free(vars->input);
		free(vars->output);
	}
	ft_clear (message, 6);
	exit(1);
}

void	my_fopen(t_vars *vars)
{
	vars->fd_in = open(vars->input, O_RDWR, 0777);
	vars->fd_out = open(vars->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (vars->fd_out == -1)
		exit_message (0, vars);
	if (vars->fd_in == -1)
		exit_message (5, vars);
	dup2(vars->fd_in, 0);
	dup2(vars->fd_out, 1);
	close(vars->fd_in);
	close(vars->fd_out);
	return ;
}
