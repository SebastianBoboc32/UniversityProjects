is_member([H|_],X):-
    H =:= X,
    !.
is_member([H|T],X):-
    H =\= X,
    is_member(T,X).

difference([],_,[]).
difference([H|T],L2,[H|Result]):-
    \+ is_member(L2,H),
    difference(T,L2,Result).
difference([H|T],L2,Result):-
    is_member(L2,H),
    difference(T,L2,Result),
    !.

