reverse_list(List, Reversed) :- reverse_list(List, [], Reversed).

reverse_list([], Reversed, Reversed).
reverse_list([H|T], Acc, Reversed) :-
    reverse_list(T, [H|Acc], Reversed).

construct_product(List1,ResultList,Remainder):- reverse_list(List1,List2),
    construct_product(List1,List2,ResultList,Remainder).

