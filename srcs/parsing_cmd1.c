/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:44:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/03 16:18:59 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fsq_cmd2(char quote, t_parser *parser, int i, t_env *env)
{
	while (parser->parser_cmd[i] != quote)
	{
		if (parser->parser_cmd[i] == '$' && parser->parser_cmd[i + 1] != '?')
			i = get_var_env_cmd(parser, i, env, 1);
		else if (parser->parser_cmd[i] == '$' && \
				parser->parser_cmd[i + 1] == '?')
		{
			if (ft_strlen(ft_itoa_base(g_code, 10)) > 0)
				parser->parser_count += ft_strlen(ft_itoa_base(g_code, 10));
			else
				parser->parser_count++;
			i += 2;
		}
		else
		{
			parser->parser_count++;
			i++;
		}
	}
	return (i);
}

static int	fsq_cmd3(char quote, t_parser *parser, int i, t_env *env)
{
	if (quote == '\'')
	{
		while (parser->parser_cmd[i] != quote)
		{
			parser->parser_count++;
			i++;
		}
	}
	else
		i = fsq_cmd2(quote, parser, i, env);
	return (i);
}

int	found_second_quote_cmd(t_parser *parser, int i, char quote, t_env *env)
{
	int	result;
	int	tmp;

	result = 0;
	if (parser->parser_cmd[i + 1])
		i += 1;
	else
		return (-1);
	tmp = i;
	while (parser->parser_cmd[i])
	{
		if (parser->parser_cmd[i] == quote)
		{
			result = 1;
			break ;
		}
		i++;
	}
	i = tmp;
	if (result)
		i = fsq_cmd3(quote, parser, i, env);
	else
		return (-1);
	return (i);
}
