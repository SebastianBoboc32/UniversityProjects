reverse_list(L1, L2) :- reverse_list(L1, [], L2).
reverse_list([], L2, L2).
reverse_list([H|T], Acc, Reversed) :-
    reverse_list(T, [H|Acc], Reversed).

compute_product(InitialList,Digit,ResultList):-
    reverse_list(InitialList,ReversedInitial),
    reverse_list(ResultList,ReversedResult),
    compute_product(ReversedInitial,Digit,ReversedResult,0).

compute_product([],_,[Carry],Carry).
%compute_product([],_,[],_).
compute_product([H|T],Digit,[NewElem|T1],Carry):-
    Temp is H*Digit+Carry,
    NewElem is Temp  mod 10,
    NewCarry is Temp//10,
    compute_product(T,Digit,T1,NewCarry).
