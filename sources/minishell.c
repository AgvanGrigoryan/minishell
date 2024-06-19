/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:06:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/19 22:24:13 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utilities.h"
#include "syntaxer.h"
#include "builtin.h"
#include "executor.h"
#include "pipex.h"

int	g_exit_status = 0;

char	*read_all(int fd)
{
	if (fd == -1)
		return ("-1");
	else if (fd == 0)
		return ("NULL");
	char *buff = malloc(1000001);
	if (buff == NULL)
		return (NULL);
	int readed = read(fd, buff, 1000000);
	buff[readed] = '\0';
	return (buff);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	return (s);
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	(void) argv;
	if (argc > 1)
		perror_exit(INVALID_ARG_CNT, NULL, NULL, 1);
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(env);
	shell->cmds = NULL;
	check_env(shell);
	token_list = NULL;
	cmd_line = "";

	while (cmd_line)
	{
		set_signal(0, signal_handler_int);
		set_signal(1, signal_handler_quit);
		cmd_line = readline("\e[1;34mMINISHELL HOPAR: \e[0m");
		if (cmd_line && *cmd_line)
		{
			add_history(cmd_line);
			tokenization(cmd_line, &token_list);
			if (syntax_validator(token_list) == 2)
				printf("EROR HAPPENED, not definied yet\n");
			expander(token_list, shell->envr, &token_list);
			if (token_list)
			{
				token_to_cmds(shell, token_list);
				ft_token_list_clear(&token_list);
				run_cmds(shell);
			}
			clear_cmds(shell);
		}
		free(cmd_line);
	}
	printf("exit\n");
	rl_clear_history();
}
