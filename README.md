# msh

My try on creating a minishell

## Test builtins

```c

char **av = ft_split(shell, ' ');
int ac = 0; while (av[ac]) ac++;
run_builtin(ac, av, env);

// wildcard match

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
