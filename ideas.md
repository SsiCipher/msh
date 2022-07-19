# Ideas

## syntax check

- '<<'	->	limiter	-> msh: syntax error: expected limiter after '<<'
- '>'	->	file	-> msh: syntax error: expected file after '>'
- '<'	->	file	-> msh: syntax error: expected file after '<'
- '>>'	->	file	-> msh: syntax error: expected file after '>>'
- '|'	->	cmd		-> msh: syntax error: expected cmd after '|'
- '&&'	->	cmd		-> msh: syntax error: expected cmd after '&&'
- '||'	->	cmd		-> msh: syntax error: expected cmd after '||'
- '"''	->	quote	-> msh: syntax error: expected a matching '"''

## steps

1. read input
2. tokenize
3. preprocess
4. syntax check
5. execute heredocs
6. build the AST
7. execute
8. repeat

## tasks

- [x] start variable expansion
- [x] wildcard expansion
- [x] syntax validation check
	- [x] find a convenient way to display errors
	- [x] start checking cmd syntax & display errors
- [x] start a heredoc + var expansion inside
	- [x] handle here_docs
	- [x] variable expansion in here_docs
	- [x] multiple here_docs for the same cmd
- [ ] build the AST and start executing

# TODO
- [ ] handle `e"$VAR"o sdfs` while VAR=cho
- [ ] before executing open & create all in/out files before executing (to handle no cmd redirection)
