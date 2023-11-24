count_occurences([],_,0).
count_occurences([H|T],X,Counter):-
    H =:= X,
    count_occurences(T,X,NewCounter),
    Counter is NewCounter +1.
count_occurences([H|T],X,Counter):-
    H \= X,
    count_occurences(T,X,Counter).

construct_unique(L1,L2):-
    construct_unique(L1,L1,L2).

construct_unique([],[],[]).

construct_unique([H|T],CopyOfList1,[H|L2]):-
    count_occurences(CopyOfList1,H,1),
    construct_unique(T,CopyOfList1,L2).

construct_unique([H|T],CopyOfList1,L2):-
    count_occurences(CopyOfList1,H,Mata),
    Mata > 1,
    construct_unique(T,CopyOfList1,L2).


