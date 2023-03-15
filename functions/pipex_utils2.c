/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:55:24 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 03:55:41 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	my_proccesses(t_vars *vars, int i)
{
	int	id1;
	int	id2;
	int	fd[2];

	if (pipe(fd) == -1)
		exit_message(2, vars);
	id1 = fork();
	if (id1 == -1)
		exit_message(1, vars);
	else if (id1 == 0)
		my_execve(vars, i, 1, fd);
	else
	{
		id2 = fork();
		if (id2 == -1)
			exit_message(1, vars);
		if (id2 == 0)
			my_execve(vars, i + 1, 0, fd);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	return (1);
}