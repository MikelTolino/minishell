/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgirondo <rgirondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:38:48 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/24 19:18:52 by rgirondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	contains_digits(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i] && cmd)
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_cmd(char **cmd)
{
	if (len_array(cmd) > 2)
	{
		throw_error("Error: Too many arguments");
		g_global.exit_status = 1;
		return (1);
	}
	printf("exit\n");
	if (!contains_digits(cmd[1]))
	{
		throw_error("Error: Bad expression");
		exit(255);
	}
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd[1]));
	return (1);
}
