# Ideas

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