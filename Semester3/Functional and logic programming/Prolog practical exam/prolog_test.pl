noOccurences([],_,0).
noOccurences([H|T],X,NewNrOc):-
    H =:=X,
    noOccurences(T,X,NrOc),
    NewNrOc is NrOc+1.
noOccurences([H|T],X,NrOc):-
    H =\=X,
    noOccurences(T,X,NrOc).


is_member([H|_],X):-
    H =:= X,
    !.
is_member([H|T],X):-
    H =\=X,
    is_member(T,X).

compute_result(L1,L2):-
    compute_result(L1,[],L2).

compute_result([],Acc,Result):-
    combine_elem_freq(Acc,Result).
compute_result([],Acc,Acc).
compute_result([H|T],Acc,Result):-
    (   \+ is_member(Acc,H) ->
           noOccurences([H|T],H,Freq),
           compute_result(T,[H,Freq | Acc],Result)
          ;compute_result(T,Acc,Result)
    ).

combine_elem_freq([],[]).
combine_elem_freq([H1,H2|T],[[H1,H2]|L2]):-
    combine_elem_freq(T,L2).
