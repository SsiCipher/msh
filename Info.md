# Ideas

## cases

- echo *$NON_VALID => expand wildcard
- echo *$VALID => expand variable

- echo "*"*

- cmd > file
- cmd < file
- cmd >> file
- cmd << limiter
- \> file cmd
- < file cmd
- \>> file cmd
- << limiter cmd
- cmd | cmd
- cmd && cmd
- cmd || cmd
- (cmd_group) && (cmd_group)
- (cmd_group) || (cmd_group)

## Notes

- handle if env var not found anywhere I interact with env
- (a && b) | c
- change all printf to write to stderr (use ft_fprintf)

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
- [x] better parsing errors
- [ ] integrate ast & further improve it (test using it: traverse, fork, dup, exec)
- [ ] handle here_docs as input redirection
- [x] understand & handle parenthesis in AST
- [ ] improve folder structure and file naming
- [x] revisit builtin commands
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
	- argc == 1	=>	exit							          = exit(0)
	- argc == 2	=>	exit 1; exit 255; exit 256  = exit(argv[1])
	- argc == 2	=>	exit m							        = exit(2) + error
	- argc == 2	=>	exit 9223372036854775808		= exit(2) + error
	- argc > 2	=>	exit 1m 3 4						      = exit(2) + error
	- argc > 2	=>	exit 1 2; exit 89 2342 3		= no exit + error + exit_code = 1
	- argc > 2	=>	exit 4 2m 23L					      = no exit + error + exit_code = 1

- fix segfault in cd -> mkdir t - cd t - rm t - cd ../t
  - do anything while in directory that is deleted

- in heredoc limiter just remove quotes no expansion
- if redirection and prev is not a cmd use it for next cmd (new case to create a node in ast tree without argv)
- export
  - new variable no value
  - new variable with value
  - update variable with new value
  - update variable with concat value

- variable expansion
  - $VAR
  - "$VAR"
  - '$VAR'
  - str $VAR str
  - str"$VAR"str
  - str'$VAR'str
  - str'$VAR'$VAR

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

norm > file && < file cat | grep Error | wc -l > result
