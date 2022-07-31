#include "msh.h"

t_ast_node *create_node(t_type type)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	node->type = type;
	node->argv = NULL;
	node->argc = 0;
	node->input_fd = STDIN_FILENO;
	node->output_fd = STDOUT_FILENO;
	node->exit_code = EXIT_SUCCESS;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	node_argv_push(t_ast_node *node, char *new_arg)
{
	node->argv = realloc(node->argv, sizeof(char *) * (node->argc + 2));
	node->argv[node->argc] = strdup(new_arg);
	node->argv[node->argc + 1] = NULL;
	node->argc += 1;
}

void	update_io_fds(t_ast_node *node, t_type type, char *filename)
{
	if (type == REDIRECT_IN && node->input_fd != STDIN_FILENO)
		close(node->input_fd);
	if ((type == REDIRECT_OUT || type == REDIRECT_APPEND) && node->output_fd != STDOUT_FILENO)
		close(node->output_fd);
	if (type == REDIRECT_IN)
		node->input_fd = open(filename, O_CREAT | O_RDONLY, 0666);
	if (type == REDIRECT_OUT)
		node->output_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (type == REDIRECT_APPEND)
		node->output_fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
}

t_ast_node	*create_ast(t_token *tkns_lst)
{
	int			pipe_ends[2];
	t_ast_node	*ast_root = NULL;
	t_ast_node	*curr_node = NULL;
	t_token		*curr_tkn = tkns_lst;

	while (curr_tkn)
	{
		if (curr_tkn->type == CMD)
		{
			if (!ast_root)
			{
				curr_node = create_node(CMD);
				ast_root = curr_node;
			}
			else if (curr_node->type != CMD)
			{
				curr_node = create_node(CMD);
				ast_root->right = curr_node;
			}
			node_argv_push(curr_node, curr_tkn->content);
		}
		else if (curr_tkn->type == PIPE || curr_tkn->type == AND || curr_tkn->type == OR)
		{
			curr_node = create_node(curr_tkn->type);
			if (curr_tkn->type == PIPE)
			{
				pipe(pipe_ends);
				curr_node->input_fd = pipe_ends[0];
				curr_node->output_fd = pipe_ends[1];
			}
			curr_node->left = ast_root;
			ast_root = curr_node;
		}
		else if (curr_tkn->type == REDIRECT_IN || curr_tkn->type == REDIRECT_OUT || curr_tkn->type == REDIRECT_APPEND)
		{
			if (!ast_root)
			{
				curr_node = create_node(CMD);
				ast_root = curr_node;
			}
			else if (curr_node->type != CMD)
			{
				curr_node = create_node(CMD);
				ast_root->right = curr_node;
			}
			update_io_fds(curr_node, curr_tkn->type, curr_tkn->next->content);
			curr_tkn = curr_tkn->next;
		}
		curr_tkn = curr_tkn->next;
	}
	return (ast_root);
}
