maxim(List1,Maxi):-maxim(List1,Maxi,-1).
maxim([],Maxi,Maxi).
maxim([H|T],Maxi,CurrentMax):-
    H > CurrentMax,
    maxim(T,Maxi,H).
maxim([H|T],Maxi,CurrentMax):-
    H =< CurrentMax,
    maxim(T,Maxi,CurrentMax).

replace(List, NewList) :- maxim(List, MaxElement), replace(List, NewList, 1, MaxElement).

replace([], [], _, _).
replace([H|T], [CurrentIndex | NewList], CurrentIndex, MaxElement) :-
    H =:= MaxElement,
    CurrentIndexNew is CurrentIndex + 1,
    replace(T, NewList, CurrentIndexNew, MaxElement).
replace([_|T], NewList, CurrentIndex, MaxElement) :-
    CurrentIndexNew is CurrentIndex + 1,
    replace(T, NewList, CurrentIndexNew, MaxElement).

solveB([],[]).
solveB([H|T],[H|Result]):-
    number(H),
    solveB(T,Result).
solveB([H|T],[Replaced|Result]):-
    is_list(H),
    replace(H,Replaced),
    solveB(T,Result).
