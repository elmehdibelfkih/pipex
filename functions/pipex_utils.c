/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 10:58:58 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 11:28:34 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	bonus_proccesses(t_vars *vars, int i)
{
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
		exit_message(2, vars);
	proccess1(vars, i, fd);
	waitpid(vars->id1, &status, 0);
	proccess2(vars, i, fd);
	return (close(fd[0]), close(fd[1]), wait(NULL), wait(NULL), 1);
}

void	proccess1(t_vars *vars, int i, int *fd)
{
	int	fd_tmp;

	vars->id1 = fork();
	if (vars->id1 == -1)
		exit_message(1, vars);
	else if (vars->id1 == 0)
	{
		if (i != 1)
		{
			fd_tmp = open("tmpfile", O_RDWR | O_CREAT, 0777);
			if (fd_tmp == -1)
				exit_message(7, vars);
			if (dup2(fd_tmp, 0) == -1)
				exit_message(8, vars);
		}
		my_execve(vars, i, 1, fd);
	}
	return ;
}

void	proccess2(t_vars *vars, int i, int *fd)
{
	int	fd_tmp;

	vars->id2 = fork();
	if (vars->id2 == -1)
		exit_message(1, vars);
	if (vars->id2 == 0)
	{
		if ((i + 1) != vars->i)
		{
			fd_tmp = open("tmpfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (fd_tmp == -1)
				exit_message(7, vars);
			if (dup2(fd_tmp, 1) == -1)
				exit_message(8, vars);
		}
		my_execve(vars, i + 1, 0, fd);
	}
	return ;
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

void	proccess3(t_vars *vars)
{
	int	id3;

	if (vars->i % 2 != 0)
	{
		id3 = fork();
		if (id3 == 0)
		{
			vars->fd_tmp = open("tmpfile", O_RDWR | O_CREAT, 0777);
			dup2(vars->fd_tmp, 0);
			if (execve(return_file(vars, vars->i),
					ft_split(vars->cmds[vars->i - 1], ' '), NULL) == -1)
				exit_message(4, vars);
		}
		wait(NULL);
	}
	unlink("tmpfile");
	return ;
}
