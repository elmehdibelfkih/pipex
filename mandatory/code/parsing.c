/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:44:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/13 06:27:41 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	parsing_path(t_vars *vars, char **envp)
{
	int		i;
	char	*s;

	i = -1;
	while (envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 1)
		{
			(*envp) += 5;
			vars->path = ft_split(*envp, ':');
			break ;
		}
		envp++;
	}
	while (vars->path[++i])
	{
		s = vars->path[i];
		vars->path[i] = ft_strjoin(s, "/");
		free (s);
	}
	return ;
}

void	parsing_args(t_vars *vars, char **argv, int argc)
{
	int	i;

	vars->cmds = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!vars->cmds)
		return ;
	vars->i = argc - 3;
	vars->cmds[argc - 3] = NULL;
	vars->input = ft_strdup(argv[1]);
	vars->output = ft_strdup(argv[argc - 1]);
	i = 0;
	while (argv[++i + 1] && i < argc - 2)
		vars->cmds[i - 1] = ft_strdup(argv[i + 1]);
	return ;
}

char	*return_file(t_vars *vars, int i)
{
	char	*path;
	char	**cmds;
	if (i > vars->i - 1)
		return (NULL);
	cmds = ft_split((*(vars->cmds + i)), ' ');
	if (access(cmds[0], X_OK) == 0)
		return (cmds[0]);
	while (*vars->path)
	{
		path = ft_strjoin(*vars->path, cmds[0]);
		if (access(path, X_OK) == 0)
		{
			ft_clear(cmds, 1000);
			return (path);
		}
		else
			free (path);
		vars->path++;
	}
	write(vars->trm, cmds[0], ft_strlen(cmds[0]));
	ft_clear(cmds, 1000);
	exit_message(3, vars);
	return (NULL);
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
		exit_message(1, vars);
	if (id1 == 0)
		my_execve(vars, i, 1, fd);
	if (id1 != 0)
		id2 = fork();
	if (id2 == -1)
		exit_message(1, vars);
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
	t = ft_split(vars->cmds[i], ' ');
	if (execve(path, t, NULL) == -1)
		exit_message(4, vars);
	return (1);
}
