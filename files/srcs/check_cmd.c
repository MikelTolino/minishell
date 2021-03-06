/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:50:51 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/25 02:47:21 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_slash(char *path)
{
	char	*new_path;

	if (!path)
		return (NULL);
	new_path = ft_strjoin(path, "/");
	return (new_path);
}

char	*search_cmd(char *cmd, char **paths)
{
	int		i;
	char	*aux;
	char	*full_cmd;

	i = 0;
	while (paths[i])
	{
		aux = add_slash(paths[i]);
		full_cmd = ft_strjoin(aux, cmd);
		free(aux);
		if (!(access(full_cmd, X_OK)))
			return (full_cmd);
		else
			free(full_cmd);
		i++;
	}
	return (NULL);
}

int	check_access(char **cmd, char **paths)
{
	char	*new_cmd;

	new_cmd = NULL;
	if (!(access(*cmd, X_OK)))
	{
		dfree(paths);
		return (1);
	}
	else
	{
		new_cmd = search_cmd(*cmd, paths);
		dfree(paths);
		if (new_cmd)
		{
			free(*cmd);
			*cmd = new_cmd;
			return (1);
		}
	}
	return (0);
}

int	check_path(char **cmd)
{
	char	*path;
	char	**paths;

	path = getvar("PATH");
	paths = ft_split(path, ':');
	if (!*cmd || !path || !paths)
	{
		free(path);
		dfree(paths);
		return (0);
	}
	free(path);
	return (check_access(cmd, paths));
}
