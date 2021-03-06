/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:40:41 by hterras           #+#    #+#             */
/*   Updated: 2022/07/20 17:42:14 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_left_redir(char *heredoc)
{
	int		saveout1;
	int		fd;

	fd = open(heredoc, O_RDONLY);
	saveout1 = dup(0);
	close(0);
	if (fd == -1)
		printf("bash: %s: No such file or directory\n", heredoc);
	else
		dup2(fd, 0);
	return (saveout1);
}

static int	handler_dleft_redir_norm(t_parser *parser, int saveout1)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (!ft_strcmp(line, parser->parser_heredoc))
			{
				free(line);
				break ;
			}
			write(saveout1, line, ft_strlen(line));
			write(saveout1, "\n", 1);
		}
		else
			break ;
		free (line);
	}
	return (saveout1);
}

int	handler_dleft_redir(t_parser *parser)
{
	int		saveout1;

	saveout1 = open(".tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (saveout1 == -1)
		printf("Erreur lors l'exécution de la commande.");
	saveout1 = handler_dleft_redir_norm(parser, saveout1);
	if (!ft_strcmp(parser->parser_cmd, "/bin/cat"))
	{
		saveout1 = handler_left_redir(".tmp/heredoc.txt");
		return (saveout1);
	}
	return (0);
}
