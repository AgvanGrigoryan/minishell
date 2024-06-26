/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:44:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:00:36 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"
#include "tokenization.h"
#include "utilities.h"
#include "pipex.h"

extern int	g_exit_status;

char	*join(char const *s1, char const *s2)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}

char	*expand_special_var(t_env_elem *envr, char *var, int is_var)
{
	char	*result;

	result = NULL;
	if (is_var == 1 && var == NULL)
	{
		result = malloc(sizeof(char));
		if (result == NULL)
			perror_exit(MALLOC_ERR, NULL, NULL, 1);
		result[0] = '\0';
	}
	else if (is_var == 0 && ft_strcmp(var, "~") == 0)
		return (get_var_in_env(envr, "HOME", 1));
	else if (var[0] == '\0')
	{
		result = ft_strdup("$");
		if (result == NULL)
			perror_exit(MALLOC_ERR, NULL, NULL, 1);
	}
	else if (ft_strcmp(var, "?") == 0)
	{
		result = ft_itoa(g_exit_status);
		if (result == NULL)
			perror_exit(MALLOC_ERR, NULL, NULL, 1);
	}
	return (result);
}

char	*get_var_in_env(t_env_elem *envr, char *var, int is_var)
{
	char	*result;

	if (var == NULL)
		return (NULL);
	result = expand_special_var(envr, var, is_var);
	if (result != NULL)
		return (result);
	while (envr)
	{
		if (ft_strcmp(var, envr->key) == 0)
		{
			if (envr->value == NULL)
				return (expand_special_var(envr, NULL, 1));
			else
				return (ft_strdup(envr->value));
		}
		envr = envr->next;
	}
	return (expand_special_var(envr, NULL, 1));
}

char	*merge_string(char *l_part, char *var, char *r_part)
{
	char	*tmp;
	char	*res;

	tmp = join(l_part, var);
	free(l_part);
	free(var);
	res = join(tmp, r_part);
	free(tmp);
	free(r_part);
	return (res);
}

char	*agvanistan(char *str, int *i, int len, t_env_elem *envr)
{
	char	*l_part;
	char	*r_part;
	char	*var;
	int		start;
	char	*search;

	l_part = ft_substr(str, 0, *i);
	start = (*i)++;
	while (str[*i] && ft_isspace(str[*i]) == 0 && \
		str[*i] != '"' && str[*i] != '\'' && str[*i] != '$' && str[*i] != '/')
		(*i)++;
	search = ft_substr(str, start + 1, *i - start - 1);
	var = get_var_in_env(envr, search, 1);
	free (search);
	r_part = ft_substr(str, *i, len - *i);
	*i = start + ft_strlen(var);
	free(str);
	return (merge_string(l_part, var, r_part));
}
