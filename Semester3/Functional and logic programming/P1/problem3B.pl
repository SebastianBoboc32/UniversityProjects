get_max_elem(L1,MaxElem):-
    get_max_elem(L1,-1,MaxElem).
get_max_elem([],Maxi,Maxi).
get_max_elem([H|T],CurrentMaxi,Maxim):-
    H > CurrentMaxi,
    get_max_elem(T,H,Maxim).
get_max_elem([H|T],CurrentMaxi,Maxim):-
    H =< CurrentMaxi,
    get_max_elem(T,CurrentMaxi,Maxim).

remove_max(L1,L2):- get_max_elem(L1,MaxElem),remove_max(L1,MaxElem,L2).
remove_max([],_,[]).
remove_max([H|T],MaxElem,L2):-
    H =:= MaxElem,
    remove_max(T,MaxElem,L2).
remove_max([H|T],MaxElem,[H|L2]):-
    H < MaxElem,
    remove_max(T,MaxElem,L2).

