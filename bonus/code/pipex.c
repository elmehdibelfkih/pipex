/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/13 05:24:32 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	my_fopen(t_vars *vars)
{
	vars->fd_in = open(vars->input, O_RDWR, 0777);
	vars->fd_out = open(vars->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (vars->fd_out == -1 || vars->fd_in == -1)
		exit_message (0, vars);
	vars->trm = dup(1);
	dup2(vars->fd_in, 0);
	dup2(vars->fd_out, 1);
	close(vars->fd_in);
	close(vars->fd_out);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		i;

	i = 0;
	if (argc <= 3)
		exit_message (0, &vars);
	parsing_path(&vars, envp);
	parsing_args(&vars, argv, argc);
	my_fopen(&vars);
	
	// if (vars.i == 0)
		
	if (my_proccesses(&vars, i) == -1)
		exit_message(1, &vars);		
	return (0);
}

int	my_proccesses(t_vars *vars, int i)
{
	int	id1;
	int	id2;
	int	s;
	int	fd[2];

	if (pipe(fd) == -1)
		exit_message(2, vars);
	id1 = fork();
	if (id1 == -1)
		return (-1);
	if (id1 == 0)
		my_execve(vars, i, 1, fd);
	if (id1 != 0)
		id2 = fork();
	if (id2 == -1)
		return (-1);
	if (id2 == 0)
	{	
		waitpid(id1, &s, 0);
		my_execve(vars, i + 1, 0, fd);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (1);
}
