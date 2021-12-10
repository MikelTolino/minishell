/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:45:39 by mmateo-t          #+#    #+#             */
/*   Updated: 2021/12/10 18:55:49 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void throw_error(const char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void check_args(int argc)
{
	if (argc != 1)
		throw_error("Numbers of arguments invalid");
}

/* void	check_errors(int argc, char **argv, char **envp)
{
	args->paths = search_paths(envp);
	if (!args->paths)
		throw_error("Program could not detect $PATH");
	check_permissions(argv[2], argv[3], args);
} */