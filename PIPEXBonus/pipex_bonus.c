/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:59:38 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/10 11:38:05 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_firstcmd(char *argv, char **env, t_pipex *value)
{
	//t_pipex	*value;
	value->pid1 = fork();
	if (pipe (value->pipefd) == 0)
	{
		dup2(value->pipefd[1], STDOUT_FILENO);
		close(value->pipefd[1]);
		close(value->pipefd[0]);
		value->argu = funct_split(argv, ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		execve(value->path, value->argu, env);
		exit(EXIT_SUCCESS);
	}
}

void	ft_cmd(char *argv, char **env, t_pipex *value)
{
	//t_pipex	*value;
	value->pid1 = fork();
	if (pipe (value->pipefd) == 0)
	{
		dup2(value->pipefd[0], STDIN_FILENO);
		value->argu = funct_split(argv, ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		dup2(value->pipefd[1], STDOUT_FILENO);
		close(value->pipefd[0]);
		close(value->pipefd[1]);
		execve(value->path, value->argu, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		file1;
	int		file2;
	t_pipex	*value;
	int		i;

	i = 2;
	if (argc != 5)
	{
		perror("too few or too much args");
		exit(EXIT_FAILURE);
	}
	value = malloc(sizeof(*value));
	if (value)
		return (0);
	file1 = open(argv[1], O_RDONLY, 0777);
	file2 = open(argv[argc], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(file1, STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	ft_firstcmd(argv[i++], env, value);
	while (i < argc - 2)
	{
		ft_cmd(argv[i++], env, value);
	}
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}
