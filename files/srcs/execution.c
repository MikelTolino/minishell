/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:08:02 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/25 01:49:59 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent_process(pid_t pid, int p[2], int *fd_in)
{
	waitpid(pid, &g_global.exit_status, 0);
	close(p[WRITE_END]);
	*fd_in = p[READ_END];
}

int	exec_pipe(t_list *cmdlist)
{
	int		p[2];
	pid_t	pid;
	int		fd_in;
	char	**cmd;

	fd_in = STDIN_FILENO;
	cmd = NULL;
	signal(SIGINT, &nothing);
	while (cmdlist)
	{
		cmd = ((t_cmd_data *)cmdlist->content)->exec_cmd;
		if (pipe(p) < 0)
			return (throw_error("Pipe Error"));
		pid = fork();
		if (pid < 0)
			return (throw_error("Fork Error"));
		else if (!pid)
			child_process(fd_in, cmdlist, cmd, p);
		else
		{
			parent_process(pid, p, &fd_in);
			cmdlist = cmdlist->next;
		}
	}
	return (0);
}

int	exec_simple(char **cmds)
{
	pid_t	pid;

	signal(SIGINT, &nothing);
	pid = fork();
	if (!pid)
	{
		g_global.whereami = CHILD;
		signal(SIGQUIT, SIG_DFL);
		execve(cmds[0], cmds, g_global.env);
		perror("Execution error");
		exit(EXEC_ERROR);
	}
	else if (pid)
		waitpid(pid, &g_global.exit_status, 0);
	else
		perror("Fork error\n");
	return (0);
}

int	execution(t_shell *shell)
{
	t_cmd_data	*data;

	if (!shell->cmdlist)
		return (g_global.exit_status);
	data = (t_cmd_data *)shell->cmdlist->content;
	if (ft_lstsize(shell->cmdlist) > 1)
		exec_pipe(shell->cmdlist);
	else
	{
		if (!exec_builtins(data->exec_cmd))
		{
			check_path(&(data->exec_cmd[0]));
			exec_simple(data->exec_cmd);
		}
	}
	return (g_global.exit_status);
}
