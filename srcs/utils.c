/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:49 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 16:54:48 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				diff;

	diff = 0;
	while ((*s1 != '\0' || *s2 != '\0'))
	{
		diff = ft_memcmp(s1, s2, 1);
		if (diff != 0)
			return (diff);
		s1++;
		s2++;
	}
	return (diff);
}

char	**create_tab(t_env *env)
{
	t_element	*current;
	int			i;
	int			j;
	char		**tri_tab;

	i = 0;
	j = 0;
	tri_tab = NULL;
	current = env->first;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = env->first;
	tri_tab = malloc(sizeof(char *) * i + 1);
	while (current != NULL)
	{
		tri_tab[j++] = current->value;
		current = current->next;
	}
	return (tri_tab);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	display_tab(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
	{
		ft_putstr_fd(env_tab[i], 1);
		i++;
	}
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
