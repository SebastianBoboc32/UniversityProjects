selec(X, [X | Rest], Rest).
selec(X, [Head | Tail], [Head | NewTail]) :-
    selec(X, Tail, NewTail).
pairslist(L1,L2):-
     pairslist(L1,[],L2).
pairslist([], L2, L2).
pairslist([H|T], Aux, L2) :-
    (   selec([H, Count], Aux, RestOfAux)
    ->  NewCount is Count + 1,
        pairslist(T, [[H, NewCount] | RestOfAux], L2)
    ;   pairslist(T, [[H, 1] | Aux], L2)
    ).
