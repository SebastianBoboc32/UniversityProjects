gcd(A,B,Result):-
    A =:=B,
    Result is A.
gcd(A,B,Result):-
    A \= B,
    A > B,
    C is A - B,
    gcd(C,B,Result).
gcd(A,B,Result):-
    A \=B,
    A < B,
    C is B -A,
    gcd(A,C,Result).

lcm(A,B,Result):-
    gcd(A,B,GCD),
    Result is(A*B)//GCD.

lcm_of_list([Result],Result).
lcm_of_list([H1,H2|T],Result):-
    lcm(H1,H2,LCM),
    lcm_of_list([LCM|T],Result).


