/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgirondo <rgirondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:52:45 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/24 18:53:38 by rgirondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env(char **cmd)
{
	int	i;

	i = 0;
	if (len_array(cmd) > 1)
	{
		throw_error("Error: Too many arguments");
		return (1);
	}
	while (g_global.env[i])
	{
		printf("%s\n", g_global.env[i]);
		i++;
	}
	return (1);
}
