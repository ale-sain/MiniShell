/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:45:11 by alvina            #+#    #+#             */
/*   Updated: 2023/03/24 10:42:53 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_arg(char **arg, int max, char *fct)
{
    int i;

    i = 0;
    if (!arg || !*arg) 
        return (1);
    while (arg[i])
        i++;
    if (i > max)
    {
        ft_putstr_fd("femtoshell: ", 2);
        ft_putstr_fd(fct, 2);
        ft_putstr_fd(": too many arguments\n", 2);
        return (0);
    }
    return(1);
}

ptr_fun	funct(int flag)
{
	static ptr_fun	tableau[7] = {
		cd,
		echo,
		ft_env,
		ft_exit,
		export,
		pwd,
        unset
	};
	return (tableau[flag]);
}

void    execve_builtin(int flag, char **arg)
{
	ptr_fun  exec;

    if (flag == -2)
        exit(0);
    exec = funct(flag);
	exec(&arg[1]);
}

int is_builtin(char *str, int pipe)
{
    if (ft_strnstr(str, "env", 3) && ft_strlen(str) == 3)
    {
        if (!pipe)
            return (-1);
        return (2);
    }
    if (ft_strnstr(str, "echo", 4) && ft_strlen(str) == 4)
    {
        if (!pipe)
            return (-1);
        return (1);
    }
    if (ft_strnstr(str, "pwd", 3) && ft_strlen(str) == 3)
    {
        if (!pipe)
            return (-1);
        return (5);
    }
    if (ft_strnstr(str, "cd", 2) && ft_strlen(str) == 2)
    {
        if (pipe)
            return (-2);
        return (0);
    }
    if (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4)
    {
        if (pipe)
            return (-2);
        return (3);
    }
    if (ft_strnstr(str, "export", 6) && ft_strlen(str) == 6)
    {
        if (pipe)
            return (-2);
        return (4);
    }
    if (ft_strnstr(str, "unset", 5) && ft_strlen(str) == 5)
    {
        if (pipe)
            return (-2);
        return (6);
    }
    return (-1);
}