/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:11:42 by natamazy          #+#    #+#             */
/*   Updated: 2024/06/20 17:01:01 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAXER_H
# define SYNTAXER_H

# include "tokenization.h"
# include "minishell.h"

int		syntax_validator(t_token	*token_list);
void	expander(t_token *tokens, t_env_elem *envr, t_token **list);

void	dollar_opener(t_token *token, int len, t_env_elem *envr);
void	remove_empty_fields(t_token *token, int empty_fields);

#endif