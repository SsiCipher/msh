# Ideas

## cases

- echo *$NON_VALID => expand wildcard
- echo *$VALID => expand variable
- echo "*"*
- (a && b) | c

# info

(A	||	B)	&&	C
(A	&&	B)	||	C
A	||	(B	&&	C)
A	&&	(B	||	C)

norm > file && < file cat | grep Error | wc -l > result
