/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 05:00:23 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/14 09:08:50 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

typedef struct s_vars
{
	char	**path;
	char	**cmds;
	char	*input;
	char	*output;
	int		i;
	int		status;
	int		trm;
	int		fd_in;
	int		fd_out;
	int		fd_tmp;
	int		id1;
	int		id2;
}				t_vars;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		n_of_world(char const *s, char c);
int		ft_clear(char **spl, int p);
int		plen(char **spl, const char *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	exit_message(int i, t_vars *vars);
void	parsing_path(t_vars *vars, char **envp);
void	parsing_args(t_vars *vars, char **argv, int argc);
char	*return_file(t_vars *vars, int i);
void	new_proccess(t_vars *vars, int i);
int		my_proccesses(t_vars *vars, int i);
int		my_execve(t_vars *vars, int i, int j, int *fd);
void	my_fopen(t_vars *vars);
void	proccess1(t_vars *vars, int i, int *fd);
void	proccess2(t_vars *vars, int i, int *fd);
void	proccess3(t_vars *vars);

#endif
