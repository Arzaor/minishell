/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/25 12:57:42 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line, t_env *env)
{
	int	i;

	i = 1;
	parser = parsing_cmd(line, parser);
	if (!strcmp(parser->parser_cmd, "cat") || \
		!strcmp(parser->parser_cmd, "sort"))
	{
		g_code = -111;
	}
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser, env);
	if (parser->parser_right_redir == 2 || parser->parser_left_redir == 1 || \
		parser->parser_dright_redir == 4 || parser->parser_dleft_redir == 3)
		parser = parsing_heredoc(line, parser);
	return (parser);
}

t_parser	*parsing_opts(char *line, t_parser *parser)
{
	int		i;

	i = ft_strlen(parser->parser_cmd);
	i += 1;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-' && line[i + 1] == 'n')
			parser->parser_opt = 1;
		i++;
	}
	return (parser);
}

void	parsing_redirection(char *line, t_parser *parser, int i)
{
	if (!check_quote_redir(line, i))
	{
		if (line[i] == '<' && line[i - 1] != '<' && line[i + 1] != '<')
			parser->parser_left_redir = 1;
		if (line[i] == '>' && line[i - 1] != '>' && line[i + 1] != '>')
			parser->parser_right_redir = 2;
		if (line[i] == '<' && line[i + 1] == '<')
			parser->parser_dleft_redir = 3;
		if (line[i] == '>' && line[i + 1] == '>')
			parser->parser_dright_redir = 4;
	}
	if (line[i] == '\'')
		parser->parser_single_quote++;
	if (line[i] == '"')
		parser->parser_double_quote++;
}

void	parsing_handler(t_parser *parser, char *line, \
						t_env *env, char **cmds_bis)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			count++;
		i++;
	}
	if (count != ft_strlen(line))
		handler_cmd(parsing(parser, line, env), env, cmds_bis);
	free_array(cmds_bis);
	free_parser(parser);
}

void	parsing_symbols(t_parser *parser, char *line, t_env *env)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
		parsing_redirection(line, parser, i++);
	parsing_handler(parser, line, env, fast_parsing(parser, line));
}
