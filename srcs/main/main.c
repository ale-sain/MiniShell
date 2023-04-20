/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/19 01:15:55 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globale	g_g = {0};

int	main(int ac, char **av, char **env)
{
	char		*str;

	(void)ac;
	(void)av;
	(void)env;
	signal(SIGSEGV, &sig_handler);
	char *s = NULL;
	printf("s : %c\n",s[0] );
	exit(21);
	handler(0, env, NULL);
	rl_outstream = stderr;
	while (21)
	{
		ft_state(READLINE);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_handler);
		signal(SIGTSTP, SIG_IGN);
		str = readline("femtoshell > ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 2);
			handler(CLEANING, NULL, NULL);
			exit(0);
		}
		if (!str[0])
			continue ;
		add_history(str);
		first_split(str);
	}
}
