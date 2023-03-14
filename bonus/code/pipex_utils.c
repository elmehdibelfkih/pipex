/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:58:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/14 06:45:35 by ebelfkih         ###   ########.fr       */
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
	message[4] = ft_strdup("execve error !!");
	message[5] = ft_strdup("There is no input file !!");
	message[6] = ft_strdup("out file error");
	message[7] = NULL;
	write (vars->trm, message[i], strlen(message[i]));
	if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		ft_clear (vars->path, 10000);
		ft_clear (vars->cmds, 10000);
		free(vars->input);
		free(vars->output);
	}
	ft_clear (message, 7);
	exit(1);
}

void	my_fopen(t_vars *vars)
{
	vars->fd_in = open(vars->input, O_RDWR, 0777);
	vars->fd_out = open(vars->output, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (vars->fd_out == -1)
		exit_message (6, vars);
	if (vars->fd_in == -1)
		exit_message (5, vars);
	dup2(vars->fd_in, 0);
	dup2(vars->fd_out, 1);
	close(vars->fd_in);
	close(vars->fd_out);
	return ;
}

int	my_proccesses(t_vars *vars, int i)
{
	int	id1;
	int	id2;
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
		exit_message(2, vars);
	id1 = fork();
	if (id1 == -1)
		exit_message(1, vars);
	else if (id1 == 0)
	{
		if (i != 1)
			dup2(open("tmpfile", O_RDWR | O_CREAT, 0777), 0);
		my_execve(vars, i, 1, fd);
	}
	waitpid(id1, &status, 0);
	id2 = fork();
	if (id2 == -1)
		exit_message(1, vars);
	if (id2 == 0)
	{
		if ((i + 1) != vars->i)
			dup2(open("tmpfile", O_RDWR | O_CREAT | O_TRUNC, 0777), 1);
		my_execve(vars, i + 1, 0, fd);
	}
	return (close(fd[0]),close(fd[1]),wait(NULL),wait(NULL), 1);
}

int	my_execve(t_vars *vars, int i, int j, int *fd)
{
	char	*path;
	char	**t;

	if (j == 0)
		close(fd[1]);
	else
		close(fd[0]);
	dup2(fd[j], j);
	close(fd[j]);
	path = return_file(vars, i);
	t = ft_split(vars->cmds[i - 1], ' ');
	if (execve(path, t, NULL) == -1)
		exit_message(4, vars);
	return (1);
}

void	unpair_arg(t_vars *vars)
{
	int id3;

	if (vars->i%2 != 0)
	{
		id3 = fork();
		if (id3 == 0)
		{
			vars->fd_tmp = open("tmpfile", O_RDWR | O_CREAT, 0777);
			dup2(vars->fd_tmp, 0);
			if (execve(return_file(vars, vars->i), ft_split(vars->cmds[vars->i - 1], ' '), NULL) == -1)
				exit_message(4, vars);
		}
		wait(NULL);
	}
	unlink("tmpfile");
	return ;
}
