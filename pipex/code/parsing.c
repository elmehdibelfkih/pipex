/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:44:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/14 06:02:32 by ebelfkih         ###   ########.fr       */
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
	write(vars->trm, cmds[0], ft_strlen(cmds[0]));
	ft_clear(cmds, 1000);
	exit_message(3, vars);
	return (NULL);
}
