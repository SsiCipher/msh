#include "msh.h"

int exec_node(t_node *node)
{
    if (node->type == CMD)
    {
        // execute it
    }
    else if (node->type == PIPE)
    {
        // create pipe & execute left and right cmds
    }
    else if (node->type == AND)
    {
        // execute left cmd based on exit code execute right cmd
    }
    else if (node->type == OR)
    {
        // execute left cmd based on exit code execute right cmd
    }
}
