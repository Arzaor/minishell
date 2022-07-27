/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/07/27 10:41:26 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tri_tab(char **tri, int count)
{
	char	*t;
	int		j;
	int		i;

	i = 0;
	while (i < count)
	{
		while (j < count)
		{
			if (ft_strcmp(tri[i], tri[j]) < 0)
			{
				t = tri[i];
				tri[i] = tri[j];
				tri[j] = t;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void	export_arg3(char *split_space, t_env *env)
{
	char	*result;
	
	result = get_env(env, split_space);
	if (result)
	{
		ft_unset(env, split_space);
		insert_env(env, split_space);
	}
	else
		insert_env(env, split_space);
	free(result);
}

void	export_arg(t_env *env, char *value)
{
	char	**split_space;
	int		i;

	i = 0;
	split_space = ft_split(value, ' ');
	while (split_space[i])
		export_arg3(split_space[i++], env);
	free_array(split_space);
}

void	ft_export(t_env *env, char *value)
{
	char	**tri;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	if (!value)
	{
		tri = create_tab(env);
		while (tri[i])
			i++;
		count = i;
		ft_tri_tab(tri, i);
		while (j < count)
			printf("declare -x %s\n", tri[j++]);
		free(tri);
	}
	else
		export_arg(env, value);
	g_code = 0;
}
