suite: '{' stmtlist '}'
stmtlist: stmt*
stmt: expr_stmt (';'|NEWLINE)

augassign: '+=' | '-=' | '*=' | '/=' | '%=' | '&=' | '|=' | '^=' | '<<=' | '>>=' | '**=' | '//='
comp_op: '<' | '>' | '==' | '>=' | '<=' | '!='

expr_stmt: testlist (
    (augassign testlist) |
    ('=' testlist)*
)

testlist: test (',' test)*

test: (
    ('?' '{' (test '->' suite)* '}') |
    loop_test
)

loop_test: or_test ['->' NAME '@' suite]
or_test: and_test ('||' and_test)*
and_test: not_test ('&&' not_test)*
not_test: '!' not_test | comp
comp: or_expr (comp_op or_expr)*
or_expr: xor_expr ('|' xor_expr)*
xor_expr: and_expr ('^' and_expr)*
and_expr: shift_expr ('&' shift_expr)*
shift_expr: arith_expr (('<<'|'>>') arith_expr)*
arith_expr: term (('+'|'-') term)*
term: factor (('*'|'/'|'%'|'//') factor)*
factor: ('+'|'-'|'~') factor | power
power: atom trailer* ['**' factor]

atom: (
    '(' [testlist] ')' ['->' suite] |
    '[' [listmaker] ']' |
    '{' [dictsetmaker] '}' |
    NAME |
    NUMBER |
    STRING
)

listmaker: test (',' test)* [',']
dictsetmaker: test [(':'|'=') test] ((','|NEWLINE) test [(':'|'=') test])* [(','|NEWLINE)]

trailer: (
    '(' testlist ')' |
    '[' testlist ']' |
    '.' NAME
)
