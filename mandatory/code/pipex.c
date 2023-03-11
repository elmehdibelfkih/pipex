/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:41:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/11 19:51:24 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    t_vars vars;
    // int stdin1;
    // int stdout1;
    // int i = 0;
    if (argc <= 3)
        exit_message (0, &vars);
    parsing_path(&vars, envp);
    parsing_args(&vars, argv, argc);
    vars.fd_in = open(vars.input, O_RDWR, 0777);
    vars.fd_out = open(vars.output, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (vars.fd_out == -1 || vars.fd_in == -1)
        exit_message (0, &vars);
    // stdin1 = dup(0);
    // stdout1 = dup(1);
    dup2(vars.fd_in, 0);
    dup2(vars.fd_out, 1);
    // new_proccess(&vars, i);


    // while (*vars.path)
    // {
    //     printf("%s\n", *vars.path);
    //     vars.path++;
    // }
    // while (*vars.cmds)
    // {
    //     printf("%s\n", *vars.cmds);
    //     vars.cmds++;
    // }
    printf("%s\n", *vars.input);

    return 0;
}