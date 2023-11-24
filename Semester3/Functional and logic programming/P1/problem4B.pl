compute_list([],[]).
compute_list([H|T],[H,1|L2]):-
    H mod 2 =:= 0,
    compute_list(T,L2).
compute_list([H|T],[H|L2]):-
    H mod 2 =:= 1,
    compute_list(T,L2).
