/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:09:44 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 17:19:19 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_value(t_parser *parser, int s, char quote, t_env *env)
{
	if (parser->parser_args[s] == '$' && quote == '"')
		s = check_dollars(parser, s, env);
	if (parser->parser_args[s] == quote)
		s++;
	else
		printf("%c", parser->parser_args[s++]);
	return (s);
}

int	ft_show_code(t_parser *parser, int i)
{
	i += 1;
	printf("%d", g_code);
	return (i);
}

static void	ft_echo_parsing(char *arg, t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
			printf("%c", arg[i]);
		else if (arg[i] == '$' && arg[i + 1] == '?')
			i = ft_show_code(parser, i);
		else if (ft_strlen(arg) <= 1 && (arg[i] == '"' || arg[i] == '\''))
			format_quotes();
		else if (arg[i] == '"' || arg[i] == '\'')
			i = ft_check_quote(parser, i, arg[i], env);
		else if (arg[i] == '$' && arg[i + 1] != '?')
		{
			i = check_dollars(parser, i, env);
			i -= 2;
		}
		else
		{
			g_code = 1;
			printf("%s: erreur lors de l'éxecution", parser->parser_cmd);
		}
		i++;
	}
}

void	ft_echo(t_parser *parser, t_env *env)
{
	int		i;
	char	*arg;

	i = 0;
	arg = parser->parser_args;
	if (arg)
	{
		ft_echo_parsing(arg, parser, env);
		if (!parser->parser_opt)
			printf("\n");
	}
	else
		printf("\n");
}
