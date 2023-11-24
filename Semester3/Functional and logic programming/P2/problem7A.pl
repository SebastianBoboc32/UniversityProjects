get_maxim(L1,Maxim):-
    get_maxim(L1,-1,Maxim).
get_maxim([],CurrentMax,CurrentMax).
get_maxim([H|T],CurrentMax,Maxim):-
    H > CurrentMax,
    get_maxim(T,H,Maxim).
get_maxim([H|T],CurrentMax,Maxim):-
    H =< CurrentMax,
    get_maxim(T,CurrentMax,Maxim).

solve_problem(List1,ListOfResults):-
    get_maxim(List1,Maxi1),
    solve_problem(List1,1,Maxi1,ListOfResults).

solve_problem([],_,_,[]).

solve_problem([H|T],CurrentIndex,Maxi1,[CurrentIndex|ListOfResults]):-
    H =:= Maxi1,
    NewIndex is CurrentIndex +1,
    solve_problem(T,NewIndex,Maxi1,ListOfResults).
solve_problem([H|T],CurrentIndex,Maxi1,ListOfResults):-
    H < Maxi1,
    NewIndex is CurrentIndex +1,
    solve_problem(T,NewIndex,Maxi1,ListOfResults).
