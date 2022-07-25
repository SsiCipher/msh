# Ideas

## Notes

- think about unquoting: cases
  - a"$VAR"c -> abc
  - a"'$VAR'"c -> a'b'c

## Process

1. Read input from user
2. Tokenize the input
3. Perform expansions (variables & wildcard)
4. Check for syntax errors
5. Execute heredocs & add files to tokens list
6. Create AST from tokens
7. Execute the created AST

## TODO

- [ ] rewrite the lexer for better tokens
- [ ] remove unnecessary types from enum t_type
- [ ] better parsing errors
- [ ] integrate ast & further improve it (test using it: traverse, fork, dup, exec)
- [ ] improve folder structure and file naming
- [ ] revisit builtin commands
- [ ] start executing

## syntax check

- '<<'	->	limiter	-> msh: syntax error: expected limiter after '<<'
- '>'	->	file	-> msh: syntax error: expected file after '>'
- '<'	->	file	-> msh: syntax error: expected file after '<'
- '>>'	->	file	-> msh: syntax error: expected file after '>>'
- '|'	->	cmd		-> msh: syntax error: expected cmd after '|'
- '&&'	->	cmd		-> msh: syntax error: expected cmd after '&&'
- '||'	->	cmd		-> msh: syntax error: expected cmd after '||'
- '"''	->	quote	-> msh: syntax error: expected a matching '"''
