/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/11 18:59:53 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	nul_character(char *limiter)
{
	ft_putstr_fd("\nwarning: here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted ", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd(")\n", STDOUT_FILENO);
}

static void do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	printf("HERE_DOC\n");
	while (!ft_strcmp(line, limiter))
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_lstclear(lst, token_cleaner) ,free_exit(NULL));
		if (!*line)
		{
			nul_character(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter))
			break ;
		ft_putstr_fd(line, ((t_cmd *)((*lst)->content))->pfd[1]);
		if (!ft_strcmp(line, "\n"))
			ft_putstr_fd("\n", ((t_cmd *)((*lst)->content))->pfd[1]);
	}
	free(line);
}

void	here_doc(t_list **list) 
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_token	*token;
	
	tmp = (*list);
	while (tmp)
	{
		cmd = (t_cmd *)(tmp->content);
		if (cmd->red)
		{
			token = (t_token *)(cmd->red->content);
			if (token && token->type == DRIN)
				do_here_doc(list, token->value);
		}
		tmp = tmp->next;
	}
	return (opening(list));
}
