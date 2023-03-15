/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:44:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 09:57:12 by ebelfkih         ###   ########.fr       */
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
	char	**tmp;

	tmp = vars->path;
	if (i > vars->i)
		return (NULL);
	cmds = ft_split((*(vars->cmds + (i - 1))), ' ');
	if (access(cmds[0], X_OK) == 0)
		return (cmds[0]);
	while (*tmp)
	{
		path = ft_strjoin(*tmp, cmds[0]);
		if (access(path, X_OK) == 0)
			return (ft_clear(cmds, 1000), path);
		free (path);
		tmp++;
	}
	write(2, cmds[0], ft_strlen(cmds[0]));
	ft_clear(cmds, 1000);
	exit_message(3, vars);
	return (NULL);
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

void	exit_message(int i, t_vars *vars)
{
	char	**message;

	message = malloc(10 * sizeof(char *));
	message[0] = ft_strdup("invalid input !\n");
	message[1] = ft_strdup("fork error !\n");
	message[2] = ft_strdup("pipe error !!");
	message[3] = ft_strdup(" command not found !!\n");
	message[4] = ft_strdup("execve error !!\n");
	message[5] = ft_strdup("There is no input file !!\n");
	message[6] = ft_strdup("out file error\n");
	message[7] = ft_strdup("tmpfile error\n");
	message[8] = ft_strdup("dup2 error\n");
	message[9] = NULL;
	write (2, message[i], strlen(message[i]));
	if (i != 0)
	{
		ft_clear (vars->path, 10000);
		ft_clear (vars->cmds, 10000);
		free(vars->input);
		free(vars->output);
	}
	ft_clear (message, 100);
	exit(1);
}
