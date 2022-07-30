/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/07/30 13:02:08 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*create_prompt_str(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	user = get_env_var(env, "USER");
	if (!user)
		user = ft_strdup("MINISHELL");
	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin_many(
			5,
			"\e[1;32m", user, " • \e[1;36m\x1B[1;34m", cwd, "\x1B[0m » "
			);
	free(user);
	free(cwd);
	return (prompt);
}

char	*init_shell(t_env *env)
{
	char *prompt;
	char *shell;

	prompt = create_prompt_str(env);
	shell = readline(prompt);
	free(prompt);
	if (!shell)
		exit(1);
	add_history(shell);
	return (shell);
}

char	*get_type_name(t_type type)
{
	if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == HERE_DOC)
		return ("R_HEREDOC");
	else if (type == REDIRECT_APPEND)
		return ("R_APPEND");
	else if (type == REDIRECT_IN)
		return ("R_IN");
	else if (type == REDIRECT_OUT)
		return ("R_OUT");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("CMD");
}

void	print_tokens(t_token *tokens_lst)
{
	t_token	*curr_tk;

	curr_tk = tokens_lst;
	while (curr_tk)
	{
		printf("%s[%d] =\t[%s]\n", get_type_name(curr_tk->type), curr_tk->length, curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

void	print_node(t_ast_node *node)
{
	printf("%d,%d -> ", node->input_fd, node->output_fd);
	if (node->type != CMD)
		printf("%s", get_type_name(node->type));
	else
	{
		for (int i = 0; i < node->argc; i++)
			printf("%s%s", i == 0 ? "": " ", node->argv[i]);
	}
	printf("\n");
}

void	print_tree(t_ast_node *root, int level)
{
	if (!root)
		return ;
	print_tree(root->right, level + 1);
	for (int i = 0; i < level * 16; i++) printf(" ");
	print_node(root);
	print_tree(root->left, level + 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	char		*shell;
	t_token		*tokens_lst;
	t_ast_node	*ast_tree;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	while (true)
	{
		shell = init_shell(env);
		tokens_lst = create_tokens_list(shell);
		expand_shell(tokens_lst, env);
		if (!check_errors(tokens_lst))
		{
			handle_here_docs(tokens_lst, env);
			ast_tree = create_ast(tokens_lst);
			printf("> ------- Tokens ------- <\n\n");
			print_tokens(tokens_lst);
			printf("\n> ------- AST ------- <\n\n");
			print_tree(ast_tree, 0);
		}
		free(shell);
		free_tokens(&tokens_lst);
	}
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	// t_env		*env;

// 	(void)argc;
// 	(void)argv;

// 	char **av = ft_split(argv[1], ' ');
// 	int l = 0;
// 	while (av[l])
// 		l++;
// 	ft_echo(l, av);

// 	return (0);
// }
