/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:55:24 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 11:34:55 by ebelfkih         ###   ########.fr       */
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

void	here_doc(t_vars *vars, char **argv, int argc)
{
	char	*s;
	int		fd;

	s = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 1)
	{
		fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		s = get_next_line(0);
		while (!ft_strncmp(s, argv[2], (ft_strlen(s) - 1)))
		{
			write(fd, s, ft_strlen(s));
			s = get_next_line(0);
		}
		parsing_args(vars, argv + 1, argc - 1);
		vars->input = strdup("here_doc");
		vars->here_doc_status = 1;
	}
	else
	{
		parsing_args(vars, argv, argc);
		vars->here_doc_status = 0;
	}
	return ;
}
