/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:37:19 by mmeguedm          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/04/21 00:59:10 by mmeguedm         ###   ########.fr       */
=======
/*   Updated: 2023/04/19 01:15:34 by mmeguedm         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char		*path;

	if (!env || !*env)
		return (NULL);
	path = ft_strnchr(*env, "PATH", 5);
	while (*env && !path)
	{
		path = ft_strnchr(*env, "PATH=/", 6);
		env++;
	}
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*get_bin_path(char *cmd, char **path)
{
	char	*bin_path;
	int		i;
	DIR		*dir;

	dir = opendir(cmd);
	i = 0;
	bin_path = NULL;
	if (!access(cmd, X_OK) && !dir)
<<<<<<< Updated upstream
		return (free_tab(path, -1), ft_strdup(cmd));
	else if (!dir && access(cmd, X_OK) == -1 && (!path || !*path))
		return (free_tab(path, -1), NULL);
	if (!path)
		return (free_tab(path, -1), NULL);
=======
		return (free_tab(path, -1), , ft_strdup(cmd));
	else if (!dir && access(cmd, X_OK) == -1 && (!path || !*path))
		return (free_tab(path, -1), , NULL);
	if (!path)
		return (free_tab(path, -1), , NULL);
>>>>>>> Stashed changes
	while (path[i])
	{
		bin_path = ft_strjoin_path(path[i], cmd);
		if (!bin_path)
<<<<<<< Updated upstream
			return (free_tab(path, -1), exit(12), NULL);
=======
			return (free_tab(path, -1), , exit(12), NULL);
>>>>>>> Stashed changes
		if (!access(bin_path, X_OK))
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
<<<<<<< Updated upstream
	return (free_tab(path, -1), bin_path);
=======
	return (free_tab(path, -1), , bin_path);
>>>>>>> Stashed changes
}
