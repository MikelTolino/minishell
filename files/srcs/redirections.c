/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:00:24 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/25 03:19:27 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_file_redir(t_token *token)
{
	int	fd;

	fd = 0;
	if (token->type == EXIT_FILE)
	{
		fd = open(token->word, O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
			return (throw_error("Error opening a file"));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (throw_error("Error in outfile redirection"));
	}
	if (token->type == EXIT_FILE_RET)
	{
		fd = open(token->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (throw_error("Error opening a file"));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (throw_error("Error in append outfile redirection"));
	}
	return (fd);
}

int	heredoc_function(t_token *token, int *fd)
{
	limitor_function_ps(token);
	g_global.whereami = 0;
	*fd = open("heredoc.tmp", O_RDONLY);
	if (*fd < 0)
		return (throw_error("Error opening a file"));
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (throw_error("Error in limitor redirection"));
	return (0);
}

int	select_redirection(t_token *token)
{
	int	fd;

	fd = 0;
	if (token->type == OPEN_FILE)
	{
		fd = open(token->word, O_RDONLY);
		if (fd < 0)
			return (throw_error("Error opening a file"));
		if (dup2(fd, STDIN_FILENO) < 0)
			return (throw_error("Error in infile redirection"));
	}
	fd = exit_file_redir(token);
	if (token->type == LIMITOR)
		heredoc_function(token, &fd);
	if (fd)
		close(fd);
	return (0);
}

void	iterate_tokens(void *content)
{
	t_cmd_data	*cmd_data;
	t_list		*token_list;
	t_token		*token;

	cmd_data = (t_cmd_data *)content;
	token_list = cmd_data->token;
	while (token_list)
	{
		token = ((t_token *)token_list->content);
		if (select_redirection(token))
			g_global.exec = true;
		token_list = token_list->next;
	}
}

void	redirections(t_shell *shell)
{
	ft_lstiter(shell->cmdlist, iterate_tokens);
}
