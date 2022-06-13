# Ideas

## syntax check

- '>'	->	file
- '<'	->	file
- '>>'	->	file
- '<<'	->	Limiter
- '|'	->	cmd
- 'CMD'	->	arguments
- '$'	->	variable
- '&&'	->	cmd
- '||'	->	cmd
- '*'	->	anything

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
- [ ] start a heredoc + var expansion inside
- [x] wildcard expansion
- [ ] syntax validation check

## TODO

- [ ] sort * wilcard results to match bash
- [ ] find a convenient way to display errors
- [ ] start checking cmd syntax & display errors
- [ ] start here_docs + handle variable expansion in it + multiple here_docs for the same cmd
- [ ] build the AST and start executing
