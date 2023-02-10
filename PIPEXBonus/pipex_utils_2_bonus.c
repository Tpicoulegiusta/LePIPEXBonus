/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:26:55 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/03 12:22:11 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_find_path(char **env, char *cmd, t_pipex *value)
{
	int		i;
	int		j;
	int		test;

	i = 0;
	j = 0;
	while (env[i][j])
	{
		if (env[i][j] == 'P' && env[i][j + 1] == 'A' && env[i][j + 2] == 'T'
		&& env[i][j + 3] == 'H')
			break ;
		i++;
	}
	value->newenv = ft_substr(env[i], 5, ft_strlen(env[i]));
	value->goodpath = funct_split(value->newenv, ':');
	i = 0;
	test = 42;
	while (test != 0 && value->goodpath[i])
	{
		value->newenv = ft_strjoinfree(value->goodpath[i], cmd);
		test = access(value->newenv, F_OK);
		i++;
	}
	return (value->newenv);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoinfree(char *stock, char *tmp)
{
	char	*str;

	if (!stock)
	{
		stock = malloc(sizeof(char) * 1);
		stock[0] = '\0';
	}
	str = ft_strjoin(stock, tmp);
	return (str);
}
