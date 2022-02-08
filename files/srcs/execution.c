/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmateo-t <mmateo-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:08:02 by mmateo-t          #+#    #+#             */
/*   Updated: 2022/02/08 12:43:15 by mmateo-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipe(t_list *cmdlist)
{
	int	p[2];
	pid_t pid;
	int	fd_in;
	char **cmd;

	fd_in = STDIN_FILENO;
	while (cmdlist)
	{
		cmd = ((t_cmd_data *)cmdlist->content)->exec_cmd;
		if (pipe(p) < 0)
			throw_error("Pipe Error:");
		if ((pid = fork()) < 0)
			throw_error("Fork Error:");
		else if (!pid)
		{
			dup2(fd_in, STDIN_FILENO); //change the input according to the old one
			if (cmdlist->next != NULL)
				dup2(p[WRITE_END], STDOUT_FILENO);
			close(p[READ_END]);
			if (!exec_builtins(cmd))
			{
				cmd[0] = check_cmd(cmd[0]);
				execve(cmd[0], cmd, global.env);
			}
			throw_error("Execution Error:");
		}
		else
		{
			wait(&global.exit_status);
			close(p[WRITE_END]);
			fd_in = p[READ_END]; //save the input for the next command
			cmdlist = cmdlist->next;
		}
	}
}


int exec_simple(char **cmds)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		execve(cmds[0], cmds, global.env);
		perror("Execution error");
	}
	else if (pid)
		wait(&global.exit_status);
	else
		perror("Fork error\n");
	return (0);
}

int execution(t_shell *shell)
{
	t_cmd_data *data;
	t_list *list;

	list = shell->cmdlist;
	data = (t_cmd_data *)list->content;
 	if (ft_lstsize(list) > 1)
	{
		loop_pipe(list);
	}
	else
	{
		if (!exec_builtins(data->exec_cmd))
		{
			data->exec_cmd[0] = check_cmd(data->exec_cmd[0]);
			exec_simple(data->exec_cmd);
		}
	}
	return (global.exit_status);
}