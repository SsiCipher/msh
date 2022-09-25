/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 07:11:24 by cipher            #+#    #+#             */
/*   Updated: 2022/09/16 21:59:15 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*get_cmd_path(char *cmd_name, t_env *env)
{
	int		i;
	char	*path_var;
	char	**split_path;
	char	*cmd_path;

	path_var = get_var(env, "PATH");
	split_path = ft_split(path_var, ':');
	i = -1;
	while (split_path[++i])
	{
		cmd_path = ft_multijoin(3, split_path[i], "/", cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		else
			free(cmd_path);
	}
	i = -1;
	while (split_path[++i])
		free(split_path[i]);
	free(split_path);
	free(path_var);
	return (cmd_path);
}

bool	is_builtin(char *cmd)
{
	return (
		!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit")
	);
}

int	run_builtin(t_node *node, t_env *env)
{
	int		tmp_io[2];
	int		exit_code;

	dup_io(node, tmp_io);
	if (!ft_strcmp(node->argv[0], "echo"))
		exit_code = ft_echo(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "cd"))
		exit_code = ft_cd(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "pwd"))
		exit_code = ft_pwd(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "export"))
		exit_code = ft_export(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "unset"))
		exit_code = ft_unset(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "env"))
		exit_code = ft_env(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "exit"))
		exit_code = ft_exit(node->argc, node->argv, env);
	close_io(node, tmp_io);
	return (exit_code);
}

void	_run_cmd(t_node *node, t_env *env, int tmp_io[2])
{
	int	cmd_exec;

	dup_io(node, tmp_io);
	if (!ft_strchr(node->argv[0], '/'))
		cmd_exec = execve(get_cmd_path(node->argv[0], env),
				node->argv, env->content);
	else
		cmd_exec = execve(node->argv[0], node->argv, env->content);
	if (cmd_exec == -1)
		print_err("msh: Command not found: ", node->argv[0]);
}

int	run_cmd(t_node *node, t_env *env)
{
	int		pid;
	int		status;
	int		tmp_io[2];

	pid = fork();
	if (pid == 0)
		_run_cmd(node, env, tmp_io);
	close_io(node, tmp_io);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
