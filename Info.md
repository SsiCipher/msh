# Ideas

## cases

- echo *$NON_VALID => expand wildcard
- echo *$VALID => expand variable
- (A && B) || C
- A && (C || B)

# info

(A	||	B)	&&	C
(A	&&	B)	||	C
A	||	(B	&&	C)
A	&&	(B	||	C)

norm > file && < file cat | grep Error | wc -l > result
