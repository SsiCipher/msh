# msh

My try on creating a minishell

## Test builtins

```c

char **av = ft_split(shell, ' ');
int ac = 0; while (av[ac]) ac++;
run_builtin(ac, av, env);

```
