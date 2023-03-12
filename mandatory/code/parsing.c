/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:44:57 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/12 03:50:09 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void    parsing_path(t_vars *vars, char **envp)
{
    int i;
    char *s;

    i = -1;
    while (envp)
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 1) {
            (*envp) += 5;
            vars->path = ft_split(*envp, ':');
            break;
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

void    parsing_args(t_vars *vars, char **argv, int argc)
{
    int i;

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

char    *return_file(t_vars *vars, int i)
{
    char *path;
    char **cmds;

    if (i > vars->i - 1)
        return (NULL);
    cmds = ft_split((*(vars->cmds + i)), ' ');
    while (*vars->path)
    {
        path = ft_strjoin(*vars->path, cmds[0]);
        if (access(path, X_OK) == 0)
            return (path);
        else
            free (path);
        vars->path++;
    }
    return (NULL) ;
}

// void    new_proccess(t_vars *vars, int i)
// {
//     int id;
//     char *path;
//     char **t;
//     int stdin1;
//     int stdout1;
//     int fd[2];
//     pipe(fd);

//     id = fork();
//     if (id == 0)
//     {
//         wait(NULL);
//         close(fd[0]);
//         path = return_file(vars, i);
//         t = ft_split(vars->cmds[i], ' ');
//         dup2(fd[1], 1);
//         if (execve(path, t, NULL) == -1)
//             exit(0);
//     }
//     else
//     {
//         wait(NULL);
//         // dup2(1, stdout1);
//         close(fd[1]);
//         path = return_file(vars, i + 1);
//         t = ft_split(vars->cmds[i + 1], ' ');
//         dup2(fd[0], stdin1);
//         if (execve(path, t, NULL) == -1)
//             exit(0);
//     }
// }


void    my_proccesses(t_vars *vars, int i)
{
    int id1;
    int id2;
    char *path;
    char **t;
    int status;
    // int stdin;
    // int stdout;
    int fd[2];
    pipe(fd);

    id1 = fork();
    if (id1 == 0)
    {
        close(fd[0]);
        close(vars->fd_out);
        path = return_file(vars, i);
        t = ft_split(vars->cmds[i], ' ');
        dup2(fd[1], 1);
        close(fd[1]);
        close(vars->fd_in);
        if (execve(path, t, NULL) == -1)
            exit(0);
        
    }
    id2 = fork();
    if (id2 == 0)
    {
        waitpid(id1, &status, 0);
        close(fd[1]);
        close(vars->fd_in);
        dup2(fd[0], 0);
        dup2(vars->fd_out, 1);
        close(fd[0]);
        close(vars->fd_out);
        path = return_file(vars, i + 1);
        t = ft_split(vars->cmds[i + 1], ' ');
        if (execve(path, t, NULL) == -1)
            exit(0);
    }
    close(vars->fd_in);
    close(vars->fd_out);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return;
}

void my_execve(t_vars *vars, int i, int j)
{
    char *path;
    char **t;
    
    close(vars->fd_out);
    close(vars->fd_in);
    path = return_file(vars, i);
    t = ft_split(vars->cmds[i], ' ');
    if (execve(path, t, NULL) == -1)
        exit(0);
}

void	exit_message(int i, t_vars *vars)
{
	char	**message;

    (void)vars;
	message = malloc(9 * sizeof(char *));
	message[0] = ft_strdup("invalid input !");
	message[1] = ft_strdup("duplicate founded !");
	message[2] = ft_strdup("sorted !!");
	message[3] = NULL;
	write(1, message[i], strlen(message[i]));
	ft_clear(message, 3);
	exit(0);
}