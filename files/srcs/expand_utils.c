/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgirondo <rgirondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:28 by rgirondo          #+#    #+#             */
/*   Updated: 2022/02/24 20:41:37 by rgirondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_token(t_list *token_list)
{
	t_list	*new;
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->word = NULL;
	token->type = ARG;
	token->quote = 0;
	new = (t_list *)malloc(sizeof(t_list));
	new->content = token;
	new->next = token_list->next;
	token_list->next = new;
}

void	join_expand_1(char **new_str, char **cmd, int i, int type)
{
	char	*tmp;
	char	*tmp2;
	int		n_single;
	int		n_double;

	n_double = 0;
	n_single = 0;
	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_substr(cmd[0], 0, i);
	if (type == 1)
		tmp = expand_ident_2(tmp, tmp[ft_strlen(tmp) - 1]);
	tmp2 = ft_strjoin(new_str[0], tmp);
	free(new_str[0]);
	free(tmp);
	new_str[0] = tmp2;
}

void	join_expand_2(char **new_str, char **cmd, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_substr(cmd[0], 0, i);
	tmp2 = getvar(tmp);
	free(tmp);
	if (tmp2)
	{
		tmp = ft_strjoin(new_str[0], tmp2);
		free(new_str[0]);
		free(tmp2);
		new_str[0] = tmp;
	}
}
