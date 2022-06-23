/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:10:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/23 16:16:41 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_element(t_element *element, t_env *env, char *arg)
{
	t_element	*current;

	current = element;
	while (element != NULL)
	{
		element = element->next;
		if (ft_strncmp(arg, element->value, ft_strlen(arg)) == 0)
		{
			current->next = element->next;
			free(element->value);
			free(element);
			break ;
		}
		current = element;
	}
}

void	ft_unset(t_env *env, char *arg)
{
	if (arg)
		delete_element(env->first, env, arg);
}
