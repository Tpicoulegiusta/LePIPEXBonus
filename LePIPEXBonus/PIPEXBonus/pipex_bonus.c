/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:59:38 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/13 16:02:01 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
/* 
void	ft_firstcmd(char *argv, char **env, t_pipex *value, int *pipefd)
{
	int		pid1;

	pid1 = fork();
	if (pipe (pipefd) == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		value->argu = funct_split(argv, ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		execve(value->path, value->argu, env);
	}
	waitpid(pid1, NULL, 0);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
} */
void	ft_lastcmd(char *argv, char **env, t_pipex *value, int *pipefd, int file2)
{
	int		pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		//dup2(pipefd[0], STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		value->argu = funct_split(argv, ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		execve(value->path, value->argu, env);
	}
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	ft_cmd(char *argv, char **env, t_pipex *value, int *pipefd)
{
	int		pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		value->argu = funct_split(argv, ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		execve(value->path, value->argu, env);
	}	
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	main(int argc, char **argv, char **env)
{
	int		file1;
	int		file2;
	int		pipefd[2];
	t_pipex	*value;
	int		i;

	i = 2;
	/* if (argc < 5)
	{
		perror("too few args");
		exit(EXIT_FAILURE);
	} */
	value = malloc(sizeof(*value));
	if (!value)
		return (0);
	file1 = open(argv[1], O_RDONLY, 0777);
	file2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(file1, STDIN_FILENO);
	while (i < argc - 2)
		ft_cmd(argv[i++], env, value, pipefd);
	ft_lastcmd(argv[i], env, value, pipefd, file2);
	return (EXIT_SUCCESS);
}
