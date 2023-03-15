/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:21:25 by alvina            #+#    #+#             */
/*   Updated: 2023/03/15 15:15:55 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
static int	infiling(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (token->type == DRIN)
	{
		close(cmd->pfd[1]);
		cmd->infile = cmd->pfd[0];
	}
	else
	{
		fd = open(token->value, O_RDONLY);
		if (fd == 0 || fd == -1)
		{
			ft_putstr_fd(token->value, 2);
			perror(" ");
			return (0);
		}
		cmd->infile = fd;
	}
	printf("in : %d\n", cmd->infile);
	return (1);
}

static int outfiling(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (token->type == ROUT)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(token->value, 2);
		perror(" ");
		return (0);
	}
	cmd->outfile = fd;
	printf("out : %d\n", cmd->outfile);
	return (1);
}

static void	print_files(t_list *cmd)
{
	t_list *tmp;

	tmp = cmd;
	while (tmp)
	{
		printf("\n-------------------\n");
		printf("infile : %d, outfile : %d\n", ((t_cmd *)(tmp->content))->infile, ((t_cmd *)(tmp->content))->outfile);
		tmp = tmp->next;
	}
}

void    opening(t_list **cmd)
{
	t_cmd 	*content;
	t_list	*red;
	t_token *data;
	t_list  *lst;

	lst = *cmd;
	while (lst)
	{
		content = (t_cmd *)lst->content;
		red = content->red;
		while (red)
		{
			data = (t_token *)red->content;
			if (data->type == RIN || data->type == DRIN)
			{
				if (!infiling(content, data))
				{
					/* CHANGE*/
					content->infile = -1;
					content->outfile = -1;
					break;
					/* CHANGE*/
				}
			}
			else
			{
				if (!outfiling(content, data))
				{
					/* CHANGE*/
					content->infile = -1;
					content->outfile = -1;
					break;
					/* CHANGE*/
				}
			}
			red = red->next;
		}
		lst = lst->next;
	}
	print_files(*cmd);
	return mini_pipex(*cmd);
}