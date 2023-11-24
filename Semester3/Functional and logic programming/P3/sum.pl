computeSubsets([],[]).
computeSubsets([H|T],[H|R]):-
    computeSubsets(T,R).
computeSubsets([_|T],R):-
    computeSubsets(T,R).

computeSum([],0).
computeSum([H|T],Sum1):-
    computeSum(T,Sum),
    Sum1 is Sum + H.

isDivisible(N,S):-
    N mod S =:= 0.

computeASolution(L1,N,Result):-
   computeSubsets(L1,Result),
    computeSum(Result,SumOfSub),
    isDivisible(SumOfSub,N).
