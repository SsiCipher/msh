#include "msh.h"

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
