/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/08 04:47:36 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_err(char *error_msg, char *arg)
{
	if (arg)
		error_msg = ft_strjoin(error_msg, arg);
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	exit(127);
}

char	*get_cmd_path(char *cmd_name, t_env *env)
{
	char	*path_var;
	char	**split_path;
	char	*cmd_path;

	path_var = get_var(env, "PATH");
	split_path = ft_split(path_var, ':');
	for (int i = 0; split_path[i]; i++)
	{
		cmd_path = ft_multijoin(3, split_path[i], "/", cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		else
			free(cmd_path);
	}
	for (int i = 0; split_path[i]; i++)
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
	if (!ft_strcmp(node->argv[0], "echo"))
		ft_echo(node->argc, node->argv);
	else if (!ft_strcmp(node->argv[0], "cd"))
		ft_cd(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "pwd"))
		ft_pwd(node->argc, node->argv);
	else if (!ft_strcmp(node->argv[0], "export"))
		ft_export(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "unset"))
		ft_unset(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "env"))
		ft_env(node->argc, node->argv, env);
	else if (!ft_strcmp(node->argv[0], "exit"))
		ft_exit(node->argc, node->argv, env);
	return (0);
}

int	run_cmd(t_node *node, t_env *env)
{
	int		cmd_exec;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		perror("Error: fork error");
	else if (pid == 0)
	{
		if (!ft_strchr(node->argv[0], '/'))
			cmd_exec = execve(get_cmd_path(node->argv[0], env), node->argv, env->content);
		else
			cmd_exec = execve(node->argv[0], node->argv, env->content);
		if (cmd_exec == -1)
			print_err("Error: Command not found: ", node->argv[0]);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

int	exec_cmd(t_node *node, t_env *env)
{
	if (is_builtin(node->argv[0]))
		return (run_builtin(node, env));
	else
		return (run_cmd(node, env));
}

int	exec_node(t_node *node, t_env *env)
{
	if (node->type == CMD)
		return (exec_cmd(node, env));
	return (0);
}
