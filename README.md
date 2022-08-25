# msh

Minishell is a 42 cursus project to better learn the inner workings of the bash on of the most important parts in any linux system

## Test builtins

```c

// Test builtins
while (true)
{
    char *shell = init_shell(env);
    if (!shell)
        continue ;
    char **av = ft_split(shell, ' ');
    int ac = 0; while (av[ac]) ac++;
    run_builtin(ac, av, env);
}

------------

// Test wildcard match
void    test(char *pattern, char *text)
{
    bool is_match = (
        match_wildcard(pattern, text)
        && !(pattern[0] != '.' && text[0] == '.')
    );
    printf("[%s] => [%s] = %d\n", pattern, text, is_match);
}

int main() {
    test(".", "m");
    test("", "word");
    test("", "");
    test("*", "word");
    test("*", "");
    test("*******", "word");
    test("*******.c", "wor.c");
    test("*", ".sdf");
    test("s*", "s*f");

    return 0;
}

```
