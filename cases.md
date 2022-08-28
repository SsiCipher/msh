# Error Cases

## export

- `export`
    - Displays all env variables sorted in ascii order
- `export V`
    - Exports a variable named V with no value
- `export V=`
    - Exports a variable named V with an empty string as value
- `export V=1`
    - Exports a variable named V with 1 as value
- `export V+=2`
    - Appends the 2 to the value of V if it exists

## exit

> Always prints exit

- `exit`
    - Exits with exit_code of 0
- `exit 4`
    - Exits with exit_code of 4
