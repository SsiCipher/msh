# Ideas

## syntax check

- '>'	->	file	-> msh: syntax error: expected file after '>'
- '<'	->	file	-> msh: syntax error: expected file after '<'
- '>>'	->	file	-> msh: syntax error: expected file after '>>'
- '<<'	->	limiter	-> msh: syntax error: expected limiter after '<<'
- '|'	->	cmd		-> msh: syntax error: expected cmd after '|'
- 'CMD'	->	args	-> msh: syntax error: expected args after 'CMD
- '$'	->	var		-> msh: syntax error: expected var after '$'
- '&&'	->	cmd		-> msh: syntax error: expected cmd after '&&'
- '||'	->	cmd		-> msh: syntax error: expected cmd after '||'
- '*'	->	chars	-> msh: syntax error: expected chars after '*'

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
- [ ] syntax validation check
  - [ ] find a convenient way to display errors
  - [ ] start checking cmd syntax & display errors
- [x] start a heredoc + var expansion inside
  - [x] handle here_docs
  - [x] variable expansion in here_docs
  - [x] multiple here_docs for the same cmd
- [ ] build the AST and start executing

# TODO
- [x] Check double free in (echo $"USER")
- [x] turn token to a bidirectional node
- [x] handle quoted limiter for here_doc + var expansion inside
