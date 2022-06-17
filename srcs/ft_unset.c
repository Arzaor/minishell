#include "minishell.h"

static t_element* delete_element(t_element *element, t_env *env, char *arg)
{
    t_element *current, *precent;

    current = element;
    if (element == NULL)
        return NULL;
	char **split_arg = ft_split(current->value, '=');
    if (ft_strncmp(arg, split_arg[0], ft_strlen(split_arg[0])) == 0)
    {
        precent = current->next;
		if (current == env->first)
			env->first = precent;
        free(current);
        return precent;
    }
	else
    {
        element->next = delete_element(element->next, env, arg);
        return element;
    }
}

void	ft_unset(t_env *env, char *arg)
{
	delete_element(env->first, env, arg);
}
