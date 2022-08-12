# Ideas

## Notes

- handle if env var not found anywhere I interact with env
- (a && b) | c

## Process

1. Read input from user
2. Tokenize the input
3. Perform expansions (variables & wildcard)
4. Check for syntax errors
5. Execute heredocs & add files to tokens list
6. Create AST from tokens
7. Execute the created AST

## TODO

- [x] rewrite the lexer for better tokens
- [x] remove unnecessary types from enum t_type
- [ ] better parsing errors
- [ ] integrate ast & further improve it (test using it: traverse, fork, dup, exec)
- [ ] handle here_docs as input redirection
- [ ] understand & handle parenthesis in AST
- [ ] improve folder structure and file naming
- [ ] revisit builtin commands
- [ ] start executing

## syntax check

- '<<'	->	limiter	-> msh: syntax error: expected limiter after '<<'
- '>'	  ->	file	  -> msh: syntax error: expected file after '>'
- '<'	  ->	file	  -> msh: syntax error: expected file after '<'
- '>>'	->	file	  -> msh: syntax error: expected file after '>>'
- '|' 	->	cmd		  -> msh: syntax error: expected cmd after '|'
- '&&'  ->	cmd		  -> msh: syntax error: expected cmd after '&&'
- '||'	->	cmd		  -> msh: syntax error: expected cmd after '||'
- '"''	->	quote	  -> msh: syntax error: expected a matching '"''

# info

- export
  - a=1
  - a+=2
  - a
  - a=

- exit
  - print "exit"
  - over long long is not numeric value
  - alphabets is not numeric value
  - many numeric values dont exit print many args

- fix segfault in cd -> mkdir t - cd t - rm t - cd ../t
  - do anything while in directory that is deleted

- in heredoc limiter just remove quotes no expansion
- if redirection and prev is not a cmd use it for next cmd (new case to create a node in ast tree without argv)
- export
  - new variable no value
  - new variable with value
  - update variable with new value
  - update variable with concat value

A	&&	B
A	||	B

(A	&&	B)	&&	C
(A	||	B)	||	C
A	&&	(B	&&	C)
A	||	(B	||	C)

(A	||	B)	&&	C
(A	&&	B)	||	C
A	||	(B	&&	C)
A	&&	(B	||	C)
